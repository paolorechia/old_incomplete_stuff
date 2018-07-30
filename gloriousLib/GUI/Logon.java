package GUI;
import java.util.*;
import javafx.application.*;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.event.*; import javafx.geometry.*;

public class Logon extends Scene{
    static public VBox noRaiz = new VBox();

    public Logon(){
        super(noRaiz, 500, 100);
    }

    Label lblUser = new Label("Username:");
    Label lblPass = new Label("Password:");

    HBox noHButtons = new HBox();
    HBox noHUsername= new HBox();
    HBox noHPassword= new HBox();

    public Button btnLogin = new Button("Login"); 
    public Button btnQuit  = new Button("Quit");

    public TextField fldUser = new TextField();
    public TextField fldPass = new PasswordField();

    Group test = new Group();

    public void init(){

        noRaiz.setAlignment(Pos.CENTER);
        noHButtons.setAlignment(Pos.CENTER);
        noHUsername.setAlignment(Pos.CENTER);
        noHPassword.setAlignment(Pos.CENTER);

        fldUser.setPromptText("Enter username");
        fldUser.setPrefColumnCount(20);
        fldPass.setPromptText("Enter password");
        fldPass.setPrefColumnCount(20);
        
        noHUsername.getChildren().addAll(lblUser, fldUser);
        noHPassword.getChildren().addAll(lblPass, fldPass);
        noHButtons.getChildren().addAll(btnLogin, btnQuit);
        noRaiz.getChildren().addAll(noHUsername, noHPassword, noHButtons);

        btnQuit.setOnAction(new EventHandler<ActionEvent>(){
            public void handle(ActionEvent ae){
                Platform.exit();
            } 
        });
    }
}

