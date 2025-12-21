cmake_minimum_required(VERSION 3.10)
project(range_simulator)

add_executable(range_simulator main.c rangeController.c rangeKeyController.c 
    rangeCookModel.c rangeMagnetronModel.c rangeRelayModel.c rangeTimer_Model.c rangeView.c)