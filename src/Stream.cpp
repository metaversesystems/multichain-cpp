#include <multichain-cpp/Stream.hpp>
#include <iostream>

namespace metaverse
{
    Stream::Stream(MultiChain *chain, std::string name)
    {
        this->name = name;
        this->chain = chain;

        Json::Value command;
        command["method"] = "getstreaminfo";
        command["params"] = Json::arrayValue;
        command["params"].append(this->name);
        command["params"].append(true);

        Json::Value result = this->chain->Execute(command);
        if(!result["error"].isNull())
        {
            throw std::runtime_error(result["error"]["message"].asString());
        }
    }

    Stream Stream::createStreamObject(MultiChain *chain, std::string name)
    {
        return Stream(chain, name);
    }

    Item Stream::ItemPublish(std::string key, std::string data)
    {
        Json::Value command;
        command["method"] = "publish";
        command["params"] = Json::arrayValue;
        command["params"].append(this->name);
        command["params"].append(key);
        command["params"].append(data);

        Json::Value result = this->chain->Execute(command);
        if(!result["error"].isNull())
        {
            throw std::runtime_error(result["error"]["message"].asString());
        }

        return this->ItemGet(key);
    }

    Item Stream::ItemGet(std::string key)
    {
        return Item::createItemObject(this, key);
    }

    std::vector<std::string> Stream::keys_get(Json::Value keys)
    {
        Json::Value command;
        command["method"] = "liststreamkeys";
        command["params"] = Json::arrayValue;
        command["params"].append(this->name);
        command["params"].append(keys);

        Json::Value result = this->chain->Execute(command);
        if(!result["error"].isNull())
        {
            throw std::runtime_error(result["error"]["message"].asString());
        }

        std::cout << result << std::endl;

        std::vector<std::string> streamkeys;

        return streamkeys;
    }

    std::vector<std::string> Stream::KeysGet(std::vector<std::string> keys)
    {
        Json::Value keys_array = Json::arrayValue;
        for(auto k : keys) keys_array.append(k);

        if(!keys.size()) keys_array = "*";

        return this->keys_get(keys_array);
    }

    std::vector<std::string> Stream::KeysGet()
    {
        Json::Value keys_array = "*";

        return this->keys_get(keys_array);
    }
}
