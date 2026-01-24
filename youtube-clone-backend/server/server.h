#pragma once
#include <iostream>

const std::string PORT = "3490";

const int BACK_LOG = 128;

const int BUFFER_LEN = 8192;

void runServer();