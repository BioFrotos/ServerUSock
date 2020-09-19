#include <iostream>
#include<uwebsockets/App.h>
#include<thread>
#include<algorithm>
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

    vector<thread*> threads(thread::hardware_concurrency());//hardware_concurrency-max can
    transform(threads.begin(), threads.end(), threads.begin(), 
        [&latest_user_id](auto* thr) {
            return new thread(
                [&latest_user_id] {
                uWS::App().ws<UserConnection>("/*", {
                     .open = [&latest_user_id](auto* ws) {     //[&]- all variables
                            //what to do when user connecting
                            UserConnection* data = (UserConnection*)ws->getUserData();
                            data->user_id = latest_user_id++;
                            cout << "new user connected, id " << latest_user_id << endl;
                      },
                     .message = [](auto* ws, string_view message, uWS::OpCode opCode) {
                            // what to  do when receive message
                         
                      }

                    }).listen(9999, 
                        [](auto* token) {
                            if (token) {
                                cout << "Server started and listening on port 9999"<<endl;
                            }
                            else{
                                cout << "Server failed to start("<<endl;
                            }
                        }).run();
            });
        });
    for_each(threads.begin(), threads.end(), [](auto* thr) { thr->join();});
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
