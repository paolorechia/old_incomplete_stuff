package GUI;
import javafx.application.*;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.event.*;
import javafx.geometry.*;
import java.util.*;

class myBox extends HBox{
    TextField tf;
    Button   btn;
    Label    lbl;
    
    myBox(String string){
        tf  = new TextField("");
        btn = new Button(string);
        lbl = new Label(string);
        this.getChildren().addAll(lbl, tf, btn);
        this.setAlignment(Pos.CENTER);
    }
}

public class MainMenu extends Scene{
    
        static VBox rootNode = new VBox();
        Label response = new Label("Teste");

        List<HBox> boxesList = new LinkedList<HBox>();

        HBox responseBox = new HBox();
        HBox searchBox   = new HBox();
        HBox insertBox   = new HBox();
        HBox deleteBox   = new HBox();
        HBox updateBox   = new HBox();

        myBox testBox   = new myBox("Teste");

        TextField tfSearch = new TextField("");
        TextField tfInsert = new TextField("");
        TextField tfDelete = new TextField("");
        TextField tfUpdate = new TextField("");

        Button btnSearch = new Button("Search");
        Button btnInsert = new Button("Insert");
        Button btnDelete = new Button("Delete");
        Button btnUpdate = new Button("Update");
        public Button btnLogout = new Button("Logout");

        ScrollPane outputPane = new ScrollPane();

        public MainMenu(){
            super(rootNode, 500, 300);
        }
        public void init(){

            tfSearch.setPromptText("Type item to be searched");
            tfInsert.setPromptText("Type item to be inserted");
            tfDelete.setPromptText("Type item to be deleted");
            tfUpdate.setPromptText("Type item to be updated");

            searchBox.getChildren().addAll(tfSearch, btnSearch);
            insertBox.getChildren().addAll(tfInsert, btnInsert);
            deleteBox.getChildren().addAll(tfDelete, btnDelete);
            updateBox.getChildren().addAll(tfUpdate, btnUpdate);
            responseBox.getChildren().addAll(response);

            boxesList.add(searchBox);
            boxesList.add(insertBox);
            boxesList.add(deleteBox);
            boxesList.add(updateBox);
            boxesList.add(responseBox);

            rootNode.getChildren().add(outputPane);
            
            for (HBox box : boxesList){
                box.setAlignment(Pos.CENTER);
                rootNode.getChildren().add(box);
            }
            rootNode.setAlignment(Pos.CENTER);
            rootNode.getChildren().addAll(btnLogout);

            btnSearch.setOnAction(new EventHandler<ActionEvent>(){
                public void handle(ActionEvent ae){
                    response.setText("You pressed Search."); 
                }
            });
            btnInsert.setOnAction(new EventHandler<ActionEvent>(){
                public void handle(ActionEvent ae){
                    response.setText("You pressed Insert."); 
                }
            });
            btnDelete.setOnAction(new EventHandler<ActionEvent>(){
                public void handle(ActionEvent ae){
                    response.setText("You pressed Delete."); 
                }
            });
            btnUpdate.setOnAction(new EventHandler<ActionEvent>(){
                public void handle(ActionEvent ae){
                    response.setText("You pressed Update."); 
                }
            });
        }
}
