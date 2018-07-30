import GUI.*;
import DATABASE.dbInterface;
import java.util.*;
import javafx.application.*;
import javafx.scene.*;
import javafx.stage.*;
import javafx.stage.StageStyle.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.scene.input.*;
import javafx.event.*;
import javafx.geometry.*;



public class GloriousLib extends Application{
    String username;
    String password;

    Label response;
    Logon logon = new Logon(); 
    MainMenu mainMenu = new MainMenu();
    public GloriousLib(){

    }

    public static void main(String args[]){
        launch(args);
    }
    public void start(Stage mainStage){
        mainStage.initStyle(StageStyle.DECORATED);
        mainStage.setTitle("Glorious Library");
        logon.init();
        mainMenu.init();
        mainStage.setScene(logon);
        mainStage.setResizable(false);
        mainStage.show();
        logon.btnLogin.setOnAction(new EventHandler<ActionEvent>(){
            public void handle(ActionEvent ae){
                login(mainStage);
            }
        });
        mainMenu.btnLogout.setOnAction(new EventHandler<ActionEvent>(){
            public void handle(ActionEvent ae){
            mainStage.setScene(logon);
            mainStage.show();
            }
        });
        
        logon.fldUser.setOnKeyTyped(e -> fldUserHandler(e, mainStage));
        logon.fldPass.setOnKeyTyped(e -> fldUserHandler(e, mainStage));
    }
    
    public void fldUserHandler(KeyEvent e, Stage mainStage){
        String str = e.getCharacter();
        int myChar = (int) str.charAt(0); 
        switch(myChar){
            case 27:            // ESC
                System.out.println("case ESC"); 
                Platform.exit();
                break;
            case 13:
                login(mainStage);
                break;
        }
    }
    private void login(Stage mainStage){
        if (checkLogin()){
                mainStage.setResizable(true);
                mainStage.setFullScreen(true);
                mainStage.setMinWidth(800);
                mainStage.setScene(mainMenu);
                mainStage.show();
        } 
    }
    private boolean checkLogin(){
                boolean success = false;
                username = new String(logon.fldUser.getCharacters().toString());
                password = new String(logon.fldPass.getCharacters().toString());
                System.out.print("Username: ");
                System.out.println(username);
                System.out.print("Password: ");
                System.out.println(password);
                success = true;
                return success;
    }
}
