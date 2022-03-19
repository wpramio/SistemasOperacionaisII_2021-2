package webservice;

import java.io.IOException;
import java.net.URI;
import javax.ws.rs.core.UriBuilder;
import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;
import com.sun.jersey.api.core.ResourceConfig;
import com.sun.net.httpserver.HttpServer;
   
public class Servidor {

    public static void main(String[] args) throws IOException {
        URI endpoint = UriBuilder.fromUri("http://localhost/").port(9000).build();

        ResourceConfig calculadora_rc = new PackagesResourceConfig("webservice");

        try {
            HttpServer server = HttpServerFactory.create(endpoint, calculadora_rc);
            server.start();
        }
        catch(IOException ex) {
            System.out.println (ex.toString());            
        }
    }
}
