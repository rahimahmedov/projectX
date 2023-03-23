//
// Created by Rahim Ahmedov on 31.01.23.
//

#include <iostream>
#include "proto/service.grpc.pb.h"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

int main() {

    auto channel = grpc::CreateChannel("localhost:50001", grpc::InsecureChannelCredentials());
    auto stub_ = MyService::NewStub(channel);
    std::string msg = "Eleyke Salam";
    grpc::ClientContext context;
    MyRequest req;
    MyResponse res;
    req.set_msg(msg);
    grpc::Status status = stub_->call(&context, req, &res);

    std::cout << res.msg() << std::endl;

    return 0;
}
