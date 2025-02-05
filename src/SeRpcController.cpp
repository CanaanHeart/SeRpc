#include "SeRpcController.h"

using namespace std;

SeRpcController::SeRpcController()
{
    failed_ = false;
    err_text_ = "";
}

void SeRpcController::Reset()
{
    failed_ = false;
    err_text_ = "";
}

bool SeRpcController::Failed() const
{
    return failed_;
}

string SeRpcController::ErrorText() const
{
    return err_text_;
}

void SeRpcController::SetFailed(const string& reason)
{
    failed_ = true;
    err_text_ = reason;
}

void SeRpcController::StartCancel()
{

}

bool SeRpcController::IsCanceled() const
{
    return false;
}

void SeRpcController::NotifyOnCancel(google::protobuf::Closure* callback)
{

}