#include <napi.h>
#include "key_assassin.hpp"

Napi::String CleanseWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    std::string input = info[0].As<Napi::String>().Utf8Value();

    // Execute
    std::string result = ECE::KeyAssassin::Cleanse(input);

    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "cleanse"), 
                Napi::Function::New(env, CleanseWrapped));
    return exports;
}

NODE_API_MODULE(keyassassin, Init)