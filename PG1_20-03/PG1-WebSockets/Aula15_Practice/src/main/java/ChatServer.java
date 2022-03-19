import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;
import java.util.logging.Logger;

@ServerEndpoint("/chat")
public class ChatServer{

    private static Set sessions = new HashSet();
    private Logger logger = Logger.getLogger("My Log");

    @OnMessage
    public void onMessage(Session actual, String message) throws IOException {

        this.logger.info(actual.getId() + " sending message!\n");
        //Send message to
        for(Object sn : sessions) {

            Session session = (Session) sn;
            session.getBasicRemote().sendText(message);
        }

    }

    @OnOpen
    public void onOpen(Session session) {

        sessions.add(session);
        this.logger.info(session.getId() + " connected!\n");

    }

    @OnClose
    public void onClose(Session session, CloseReason closeReason) {

        this.logger.info((session.getId() + " is leaving! " + closeReason.getReasonPhrase() + "\n"));
        sessions.remove(session);

    }

}
