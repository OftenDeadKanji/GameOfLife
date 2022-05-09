#pragma once
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.hpp>
#include <string>
#include <exception>
#include <chrono>

class BoardComputeProgramFailException
	: public std::exception
{
public:
	explicit BoardComputeProgramFailException(std::string message);

	[[nodiscard]] const char* what() const override;

private:
	std::string message;
};

class Board
{
public:
	Board(int width, int height, bool withBorder);
	~Board();

	void update(float deltaTime);

	size_t getWidth() const;
	size_t getHeight() const;

	const int& operator()(int x, int y) const;
	int& operator()(int x, int y);

	void start();
	void stop();
	void restart();

	bool isUpdating() const;

	void setUpdateSpeed(float speed);
private:
	void createBoardArrays();
	void createComputeProgram();

	size_t width, height;
	size_t size;
	int withBorder;

	int* board[2] {};
	int srcBoard{ 0 };
	int dstBoard{ 1 };

	double updateSpeed{ 1.0 };
	const double defaultBreakTimeInSec{ 0.5};
	std::chrono::steady_clock::time_point lastUpdate;
	bool continueUpdating{};

	const std::string kernelSourceCodePath = "src/Kernels/GoL_OneIterate.cl";

	cl::Platform platform;
	cl::Device device;
	cl::Context context;
	cl::Program program;
	cl::Kernel kernel;

	cl::CommandQueue queue;

	cl::Buffer bufferSource;
	cl::Buffer bufferDestination;

};

