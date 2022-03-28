# Trabalho prático - etapa 1
* Processo `app_server` tem uma `main()` que inicializa um `Server` e fica escutando mensagens dos
  clientes (SESSION, FOLLOW ou SEND).
  - Inclui `Server`, `Socket`, `Session`, `Follow`.

* Processo `app_client` recebe argumentos e, se todos forem válidos, inicializa um objeto
  `ClientSession`.
  - Inclui `Validations`, `ClientSession`.


## Features pedidas no enunciado
- [x] Server abre socket e espera conexões de Clientes
- [x] Cliente consegue conectar ao socket do Server
- [x] Cliente só pode ter 2 conexões simultâneas com o Server
- [x] Decrementa o número de sessões quando o cliente executar o comando EXIT
- [x] Perfil pode seguir outro perfil com comando FOLLOW
- [x] Perfil não consegue seguir a si mesmo
- [x] Perfil não consegue seguir outro Perfil que já segue ou que não existe
- [x] Uma thread para cuidar da comunicação do Cliente com o Server, e outra para cuidar do recebimento do Feed
- [x] Perfil consegue postar tweet com comando SEND
- [x] Tweet só pode ter no máximo 128 caracteres
- [ ] Perfil que segue outro que postou tweet recebe o tweet
- [ ] Uma thread para cada cliente no servidor

