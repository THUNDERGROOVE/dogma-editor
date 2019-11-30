#!/usr/bin/env bash

cd external/imgui

git pull


cp *.cpp *.h ../../src
cp examples/imgui_impl_glfw.* ../../src
cp examples/imgui_impl_opengl3.* ../../src
