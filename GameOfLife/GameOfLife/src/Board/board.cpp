#include "board.h"

#include <iostream>
#include <vector>
#include <fstream>

BoardComputeProgramFailException::BoardComputeProgramFailException(std::string message)
	: message(std::move(message))
{}

const char* BoardComputeProgramFailException::what() const
{
	return this->message.c_str();
}

std::string load_File(const std::string& filePath)
{
	if (std::ifstream file(filePath); file.is_open())
	{
		file.seekg(0, std::ios::end);

		const size_t size = file.tellg();
		std::string buffer(size, ' ');

		file.seekg(0);
		file.read(&buffer[0], size);

		file.close();
		return buffer;
	}

	return {};
}

Board::Board(int width, int height, bool withBorder)
	: width(width), height(height), size(width * height), withBorder(withBorder)
{
	this->createBoardArrays();
	this->createComputeProgram();

	this->lastUpdate = std::chrono::steady_clock::now();
}

Board::~Board()
{
	delete[] this->board[0];
	delete[] this->board[1];
}

void Board::update(float deltaTime)
{
	if (this->continueUpdating)
	{
		const double elapsedTimeInSec = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - this->lastUpdate).count() * 0.000000001;
		if (elapsedTimeInSec * this->updateSpeed > this->defaultBreakTimeInSec)
		{
			this->queue.enqueueWriteBuffer(this->bufferSource, CL_TRUE, 0, sizeof(int) * this->size, this->board[this->srcBoard]);
			//std::cout << &this->board[this->srcBoard][0];
			//std::cout << &this->board[this->dstBoard][0];

			kernel.setArg(0, this->bufferSource);
			kernel.setArg(1, this->bufferDestination);
			//kernel.setArg(2, 1);
			//kernel.setArg(3, 1);
			//kernel.setArg(4, 1);
			kernel.setArg(2, this->width);
			kernel.setArg(3, this->height);
			kernel.setArg(4, this->withBorder);

			this->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(this->size), cl::NullRange);
			this->queue.finish();
			this->queue.enqueueReadBuffer(this->bufferDestination, CL_TRUE, 0, sizeof(int) * this->size, this->board[this->dstBoard]);

			std::swap(this->srcBoard, this->dstBoard);

			this->lastUpdate = std::chrono::steady_clock::now();
		}
	}
}

size_t Board::getWidth() const
{
	return this->width;
}

size_t Board::getHeight() const
{
	return this->height;
}

const int& Board::operator()(int x, int y) const
{
	return this->board[this->srcBoard][x * this->height + y];
}

int& Board::operator()(int x, int y)
{
	return this->board[this->srcBoard][x * this->height + y];
}

void Board::start()
{
	this->continueUpdating = true;
}

void Board::stop()
{
	this->continueUpdating = false;
}

void Board::restart()
{
	this->continueUpdating = false;

	for(int i = 0; i < this->size;++i)
	{
		this->board[0][i] = this->board[1][i] = 0;
	}
}

bool Board::isUpdating() const
{
	return this->continueUpdating;
}

void Board::createBoardArrays()
{
	for (size_t n = 0; n < 2; ++n)
	{
		this->board[n] = new int [this->size];
		for (size_t i = 0; i < this->size; ++i)
		{
			this->board[n][i] = 0;
		}
	}
}

void Board::createComputeProgram()
{
	std::vector<cl::Platform> allPlatforms;
	cl::Platform::get(&allPlatforms);
	if(allPlatforms.empty())
	{
		throw BoardComputeProgramFailException("No platforms found.");
	}

	this->platform = allPlatforms[0];
	std::cout << "Using platform: " << this->platform.getInfo<CL_PLATFORM_NAME>() << '\n';
	std::cout << "Using OpenCL Version: " << this->platform.getInfo<CL_PLATFORM_VERSION>() << '\n';

	std::vector<cl::Device> allDevices;
	this->platform.getDevices(CL_DEVICE_TYPE_GPU, &allDevices);
	if (allDevices.empty())
	{
		throw BoardComputeProgramFailException("No devices found.");
	}

	this->device = allDevices[0];
	std::cout << "Using device: " << this->device.getInfo<CL_DEVICE_NAME>() << '\n';

	this->context = cl::Context({ this->device });

	const std::string sourceCode = load_File(this->kernelSourceCodePath);
	cl::Program::Sources sources { {sourceCode.c_str(), sourceCode.size()} };

	this->program = cl::Program(this->context, sources);
	if(program.build({this->device}) != CL_SUCCESS)
	{
		throw BoardComputeProgramFailException("Building failed: " + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(this->device));
	}

	this->kernel = cl::Kernel(this->program, "gameOfLife");

	

	this->bufferSource = cl::Buffer(this->context, CL_MEM_READ_ONLY, sizeof(int) * this->size);
	this->bufferDestination = cl::Buffer(this->context, CL_MEM_WRITE_ONLY, sizeof(int) * this->size);

	this->queue = cl::CommandQueue(this->context, this->device);
}
