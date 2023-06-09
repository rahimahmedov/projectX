// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: service.proto
#ifndef GRPC_service_2eproto__INCLUDED
#define GRPC_service_2eproto__INCLUDED

#include "service.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

class MyService final {
 public:
  static constexpr char const* service_full_name() {
    return "MyService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status call(::grpc::ClientContext* context, const ::MyRequest& request, ::MyResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::MyResponse>> Asynccall(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::MyResponse>>(AsynccallRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::MyResponse>> PrepareAsynccall(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::MyResponse>>(PrepareAsynccallRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void call(::grpc::ClientContext* context, const ::MyRequest* request, ::MyResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void call(::grpc::ClientContext* context, const ::MyRequest* request, ::MyResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::MyResponse>* AsynccallRaw(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::MyResponse>* PrepareAsynccallRaw(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status call(::grpc::ClientContext* context, const ::MyRequest& request, ::MyResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::MyResponse>> Asynccall(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::MyResponse>>(AsynccallRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::MyResponse>> PrepareAsynccall(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::MyResponse>>(PrepareAsynccallRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void call(::grpc::ClientContext* context, const ::MyRequest* request, ::MyResponse* response, std::function<void(::grpc::Status)>) override;
      void call(::grpc::ClientContext* context, const ::MyRequest* request, ::MyResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::MyResponse>* AsynccallRaw(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::MyResponse>* PrepareAsynccallRaw(::grpc::ClientContext* context, const ::MyRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_call_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status call(::grpc::ServerContext* context, const ::MyRequest* request, ::MyResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_call : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_call() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_call() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status call(::grpc::ServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestcall(::grpc::ServerContext* context, ::MyRequest* request, ::grpc::ServerAsyncResponseWriter< ::MyResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_call<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_call : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_call() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::MyRequest, ::MyResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::MyRequest* request, ::MyResponse* response) { return this->call(context, request, response); }));}
    void SetMessageAllocatorFor_call(
        ::grpc::MessageAllocator< ::MyRequest, ::MyResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::MyRequest, ::MyResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_call() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status call(::grpc::ServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* call(
      ::grpc::CallbackServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_call<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_call : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_call() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_call() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status call(::grpc::ServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_call : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_call() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_call() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status call(::grpc::ServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestcall(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_call : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_call() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->call(context, request, response); }));
    }
    ~WithRawCallbackMethod_call() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status call(::grpc::ServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* call(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_call : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_call() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::MyRequest, ::MyResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::MyRequest, ::MyResponse>* streamer) {
                       return this->Streamedcall(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_call() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status call(::grpc::ServerContext* /*context*/, const ::MyRequest* /*request*/, ::MyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedcall(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::MyRequest,::MyResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_call<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_call<Service > StreamedService;
};


#endif  // GRPC_service_2eproto__INCLUDED
