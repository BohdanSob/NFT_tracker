#include <iostream>
#include <string>
#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/common/exception.h>

int main() {
    std::string url = "https://polygon-mainnet.infura.io/v3/<INFURA_API_KEY>";
    std::string contractAddress = "<NFT_Contract_Address>";
    std::string ownerAddress = "<Owner_Address>";
    /*Визначаються рядки url, contractAddress та ownerAddress, 
    які містять відповідні значення адреси API Infura, 
    адреси NFT-контракту та адреси власника.*/

    jsonrpc::HttpClient httpClient(url);
    jsonrpc::Client client(httpClient);
    /*Створюються об'єкти httpClient та client. 
    httpClient використовується для встановлення HTTP-з'єднання
    із вказаною URL-адресою, а client використовується для взаємодії з JSON-RPC-сервером.*/

    try {
        Json::Value request(Json::objectValue);
        request["jsonrpc"] = "2.0";
        request["id"] = 1;
        //request["method"] = "eth_call";
        Json::Value params(Json::arrayValue);
        params.append(ownerAddress);
        request["params"] = params;
        /*Створюється об'єкт request типу Json::Value,
         який представлятиме JSON-об'єкт запиту. Тут визначено
         ключі "jsonrpc" та "id", які відповідають версії протоколу JSON-RPC та ідентифікатору запиту.*/


        Json::Value response;
        client.CallMethod(request["method"].asString(), request, response);
        /*Створюється об'єкт response типу Json::Value,
         який міститиме відповідь від JSON-RPC-сервера.
         Потім викликається метод CallMethod об'єкта client,
         який відправляє запит request на сервер з
         вказівкою методу "eth_call" і чекає відповіді, яка зберігається у response. */


        if (!response.isNull() && response.isArray()) {
            const Json::Value& nftList = response;
            /*Перевіряється, чи є відповідним дійсним JSON-масивом.
             Якщо так, то створюється посилання nftList на response,
             ітерується по кожному елементу nft до nftList.*/


            for (const auto& nft : nftList) {
                std::string nftUrl;

                // Извлекаем URL из NFT и парсим его определенным образом

                std::cout << "NFT URL: " << nftUrl << std::endl;
            }
        }
        else if (response.isMember("error")) {
            std::cerr << "Error: " << response["error"]["message"].asString() << std::endl;
        }
    }
    catch (const jsonrpc::JsonRpcException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    /*Обробчик помилок*/
    return 0;
}
