
typedef struct reckon_request InputRequest;

struct reckon_request
{
    char* request;
    //char *strtok(char *str, const char *sep);
    char* method_data_request; // метод сообщает серверу, что пользователь хочет получить некоторые данные
    char* Ip_and_port_client; // с какого конкретного хоста отправляется запрос
    char* who_makes_request; // описание клиента который запрашивает ресурс(может содержать описание OS и браузера)
    char* accepted_file_type; // указывает какой тип файлов принимает клиент( могут быть указаны несколько типовч ерез
                  // запятую, а для указание принятия любых типов используется */*)
                  // заметка мой сервер что-то отправляет, а curl пишет Получен HTTP/0.9, когда это запрещено.
};
