package webservice;

import javax.ws.rs.core.MediaType;
import com.sun.jersey.api.client.Client;
import com.sun.jersey.api.client.ClientResponse;
import com.sun.jersey.api.client.WebResource;
import com.sun.jersey.api.client.config.ClientConfig;
import com.sun.jersey.api.client.config.DefaultClientConfig;

public class Cliente {
     
    public static void main(String[] args) {
        int a = 4, b = 10, resultado;

        ClientConfig config = new DefaultClientConfig();
        Client cliente = Client.create(config);
        WebResource servico = cliente.resource("http://localhost:9000/calculadora");

        WebResource servicoSomarInt = servico.path("somarInt").path(a + "/" + b);
        ClientResponse respostaSomarInt = servicoSomarInt.accept(MediaType.APPLICATION_JSON).
        get(ClientResponse.class);

        String respostaJsonSomarInt = respostaSomarInt.getEntity(String.class);
        System.out.println("Resposta da adicao: " + respostaJsonSomarInt);

        WebResource servicoMultiplicarInt = servico.path("multiplicarInt").path(a + "/" + b);
        ClientResponse respostaMultiplicarInt = servicoMultiplicarInt.accept(MediaType.APPLICATION_JSON).
        get(ClientResponse.class);

        String respostaJsonMultiplicarInt = respostaMultiplicarInt.getEntity(String.class);
        System.out.println("Resposta da multiplicacao: " + respostaJsonMultiplicarInt);
    }
}
