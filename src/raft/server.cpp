#include <iostream>
#include "proto/service.grpc.pb.h"
#include "proto/service.pb.h"
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>


class MyServiceImp: public  MyService::Service {
    ::grpc::Status call(::grpc::ServerContext *context, const ::MyRequest *request, ::MyResponse *response) override {

        auto resp = new std::string(request->msg());
        resp->append(" - response.");
        response->set_allocated_msg(resp);
        return grpc::Status::OK;
    }
};

void run_server(const std::string& server_address) {
    MyServiceImp myServiceImp;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&myServiceImp);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}


int main() {
    //std::cout << "Hello, World!" << std::endl;
    run_server("localhost:50001");
    return 0;

}
