#include <iostream>
#include<uwebsockets/App.h>
using namespace std;

// struct for storage user data
struct UserConnection {
    unsigned long user_id;
    string* user_name;
};

    //"ws://127.0.0.1/" url
    //ws веб сокет
    //.open -lambda function

int main()
{
    unsigned long latest_user_id = 10;
    uWS::App().ws<UserConnection>("/*",{
        .open = [&](auto* ws) {     //[&]- all variables
            //what to do when user connecting
            UserConnection* data=(UserConnection* )ws->getUserData();
            data->user_id = latest_user_id++;
        },
        .message = [](auto* ws, string_view message, uWS::OpCode opCode) {
            // what to  do when receive message

        }
});
   
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
