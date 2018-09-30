//
//  main.cpp
//  OpenCLProgrammingGuideLesson1
//
//  Created by James WoMa
//
/*
 
 This opencl program finds the platforms and devices,
 allows the user to choose which platform and device they want,
 and creates a corresponding context
 
 */


#include <OpenCL/opencl.h>
#include <iostream>


cl_context CreateContext(){
    std::cout << "Welcome to OpenCL!" << '\n';
    cl_int errNum;
    cl_uint numPlatforms;
    cl_context context = NULL;
    
    errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (errNum != CL_SUCCESS || numPlatforms <= 0){
        std::cout << "Failed to find any OpenCL platforms." << std::endl;
        return NULL;
    }
    
    cl_platform_id* platformlist = (cl_platform_id*)malloc(sizeof(cl_platform_id)*numPlatforms);
    
    errNum = clGetPlatformIDs(numPlatforms, platformlist, NULL);
    if (errNum != CL_SUCCESS || numPlatforms <= 0){
        std::cout << "Failed to find any OpenCL platforms." << std::endl;
        return NULL;
    }
    
    //choose platform from list
    std::cout << "Choose the number of the platform you would like to use:" << std::endl;
    
    int buffer_size = 10540;
    char buffer[buffer_size];
    for (int i = 0; i < numPlatforms; i++){
        clGetPlatformInfo(platformlist[i], CL_PLATFORM_NAME, sizeof(char)*buffer_size, buffer, NULL);
        std::cout << "[" << i << "] " << buffer << std::endl;
    }
    
    int platform_choice;
    std::cin >> platform_choice;
    
    //choose device from list
    cl_uint numDevices;
    errNum = clGetDeviceIDs(platformlist[platform_choice], CL_DEVICE_TYPE_ALL, NULL, NULL, &numDevices);
    if (errNum != CL_SUCCESS || numDevices <= 0){
        std::cout << "Failed to find any OpenCL devices." << std::endl;
        return NULL;
    }
    
    std::cout << "Error is right after this" << '\n';
    
    
    
    cl_device_id* devicelist = (cl_device_id*)malloc(sizeof(cl_device_id)*numDevices);
    
    errNum = clGetDeviceIDs(platformlist[platform_choice], CL_DEVICE_TYPE_ALL, NULL, devicelist, NULL);
    if (errNum != CL_SUCCESS || numDevices <= 0){
        std::cout << "Failed to find any OpenCL devices." << std::endl;
        return NULL;
    }
    
    /*
     I used this command correctly in the previous command, but I don't seem to be using it correctly this second time.
     */
    
    
    
    
    std::cout << "Choose the number of the device you would like to use:" << std::endl;
    for (int i = 0; i < numDevices; i++){
        clGetDeviceInfo(devicelist[i], CL_DEVICE_NAME, sizeof(char)*buffer_size, buffer, NULL);
        std::cout << "[" << i << "] " << buffer << std::endl;
    }
    
    int device_choice;
    std::cin >> device_choice;
    
    
    cl_context_properties contextProperties[] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platformlist[0],
        0
    };
    
    context = clCreateContextFromType(contextProperties,
                                      CL_DEVICE_TYPE_GPU,
                                      NULL, NULL, &errNum);
    if (errNum != CL_SUCCESS)
    {
        std::cout << "Could not create GPU context, trying CPU..." << std::endl;
        context = clCreateContextFromType(contextProperties,
                                          CL_DEVICE_TYPE_CPU,
                                          NULL, NULL, &errNum);
        if(errNum != CL_SUCCESS)
        {
            std::cout << "Failed to create an OpenCL GPU or CPU context." << std::endl;
            return NULL;
        }
        
    }
    
    return context;
}

int main(int argc, const char * argv[]) {
    CreateContext();
    return 0;
}
