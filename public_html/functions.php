<?php

function queryQueue($queue, $connection){
    $length = count($queue);
    for ($i = 0; $i < $length; $i++){
        $result = mysqli_query($connection, $queue[$i]);
        printResult($result, $connection);
    }
}

function SQLizeAllTables($tab_names){
    $length = count($tab_names);
    for ($i = 0; $i < $length; $i++){
        $SQLQueue[$i] = "select * from " . $tab_names[$i];
    }
    return $SQLQueue;
}

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

function dropdown_button($query, $tab_names, $id){
    echo "<select onmouseup='sendDoubleAJAX(
    " . '"' . $query . '",' . "this.value, " . '"' . $id . '"' . ")'>";
    $length=count($tab_names);
    for ($i=0; $i<$length; $i++){
        echo "<option value='" . $tab_names[$i] . "'>" . $tab_names[$i] .
             "</option>";
    }
    echo "</select>";
}
function dropdown_debug($query, $tab_names, $id){
    echo "<select onmouseup='debugAJAX(
    " . '"' . $query . '",' . "this.value, " . '"' . $id . '"' . ")'>";
    $length=count($tab_names);
    for ($i=0; $i<$length; $i++){
        echo "<option value='" . $tab_names[$i] . "'>" . $tab_names[$i] .
             "</option>";
    }
    echo "</select>";
}
function SelectTable($tab_name, $connection){
    $sql = "select * from " . $tab_name;
    $result = mysqli_query($connection, $sql);
    return printResult($result, $connection);
}

function searchTable($tab_name, $campo, $entrada, $connection){
    $sql = <<<SUPA
    SELECT * FROM $tab_name WHERE $campo LIKE '%$entrada%';
SUPA;
    $result = mysqli_query($connection, $sql);
    return printResult($result, $connection);
}

function fetchTablesNames($tables, $database){
    $string="Tables_in_" . $database;
    $i = 0;
    foreach ($tables as $elemento){
        $tab_names[$i] = $elemento[$string];
        $i++;
    }
    return $tab_names;
}
function fetchDBNames($result){
    $i=0;
    foreach ($result as $element){
        $names[$i]=$element["Database"];
        $i++;
    }
    return $names;
}

            
function printResult($result, $connection){
    if (mysqli_num_rows($result) > 0) {
        // output data of each row
        $length = mysqli_field_count($connection);
        $fields = mysqli_fetch_fields($result);

        for ($i = 0; $i < $length; $i++){
            $names_array[$i] =$fields[$i]->name;
        }
        echo "<br>";
        echo "<div class='table-responsive'>";
        echo "<table class='table' width='100%'>";
        echo "<tr class='first'>";
        for ($i = 0; $i < $length; $i++){ 
            echo "<th>" . $names_array[$i]  . "</th>";
        }
        echo "</tr>";
        while($row = mysqli_fetch_array($result, MYSQLI_NUM)) {
            echo "<tr>";
            for ($i = 0; $i < $length; $i++){
                echo "<td>" . $row[$i] . "</td>";
            }
            echo "</tr>";
        }
        echo "</table>";
        echo "</div>";
    }
    else {
        echo "0 results. <br>";
    }
    echo "<br>";
    return $names_array;
}

function buildButton($nome, $csv_fields, $query_type, $html_id, $button_string){

//    $id=crypt($button_string);
    $string= <<<SUPER
    <button id='$button_string'
     onmouseup='fetchInput("$nome", 
                           "$csv_fields", 
                           "$query_type",
                           "$html_id")'>
    $button_string  </button>
SUPER;
    echo $string;
}
function resetBuffer(){
    $_SESSION["buffer"] = "";   // reseta buffer de busca   // reseta buffer de busca
}
function printButtons($nome, $connection, $fields){
    resetBuffer();
    $_SESSION["current_table"] = $nome;
    $_SESSION["fields"]        = $fields;
    echo "<form class = 'form-inline' >";
    $i = 0;
    foreach ($fields as $field){
        $id = $nome . "_" . $field;
        $string = <<<TESTE
        $field: <input type='text'
                 onkeydown='fetchKey(event, "$field", "$nome", "$id")'
                 name='$field'
                 id='$id' >
TESTE;
        echo $string;
        $csv_fields = $field . "," . $csv_fields;
    }
    echo "</form>";

    buildButton($nome, $csv_fields, "insert", "select", "Insert new row");
    buildButton($nome, $csv_fields, "delete", "select", "Delete a row"  );
    buildButton($nome, $csv_fields, "update", "select", "Update a row"  );
}

function insereLinha($connection){
    $name = $_SESSION["current_table"];
    $entrada = test_input($_REQUEST['input']);
    $fields = $_SESSION["fields"];
    foreach ($fields as $campo){
        $campos = $campos . $campo . ",";
    }
    $final = strlen($campos) - 1;
    $campos = substr($campos, 0, $final);


    $sql = "INSERT INTO " . $name;
    $sql = $sql . " (" . $campos . ") ";
    $sql = $sql . "VALUES (" . $entrada . ");";
    echo $sql . "<br>";
    $result = mysqli_query($connection, $sql);
    if(!$result){
        echo "Insercao impossivel <br>";
    }
}
function removeLinha($connection){
    $name = $_SESSION["current_table"];
    $entrada = test_input($_REQUEST['input']);
    $fields = $_SESSION["fields"];

    $length = count($fields);
    $entrada = trim($entrada, " ");
    $vetor_entrada = explode("," , $entrada);

    $valid_input = 0;
    for ($i = 0 ; $i < $length; $i++){
        $entrada = $vetor_entrada[$i];
        if (strlen($entrada) > 2){
            $vetor_sql[$i] = $fields[$i] . "=" . $entrada;
            $valid_input = 1;
        }
    }
    
    
    if ($valid_input){
        $sql = "DELETE FROM " . $name . " WHERE ";
        $setAND = 0;
        for ($i = 0; $i < $length; $i++){
            if ($vetor_sql[$i] != NULL){
                if ($setAND){
                    $sql = $sql . " AND " . $vetor_sql[$i];
                }
                else{
                    $setAND=1;
                    $sql = $sql . $vetor_sql[$i];
                }
            }
        }
        echo $sql . "<br>";
        $result = mysqli_query($connection, $sql);
        if(!$result){
            echo "Remocao impossivel <br>";
        }
    }
    else{
        echo "Entrada invalida <br>";
    }
}
function atualizaLinha($connection){
    $name = $_SESSION["current_table"];

    $fields = $_SESSION["fields"];
    echo "fields = " . $fields . "<br>";

    foreach ($fields as $campo){
        $campos = $campos . $campo . ",";
    }
    $final = strlen($campos) - 1;
    $campos = substr($campos, 0, $final);
    echo "campos = " . $campos . "<br>";

    $entrada = test_input($_REQUEST['input']);
    $entradas = explode(",", $entrada);
    echo "entradas = " . $entradas . "<br>";


    $len = count($entradas);
    for ($i = 0; $i < $len ; $i++){
        if (strlen($entradas[$i]) > 2){
              echo $entradas[$i] . "<br>";
              $campos=<<<HEREDOC
              WHERE $fields[$i]='$entradas[$i]'.
HEREDOC;
//            $campos= $fields[$i] . "=" . $entradas[$i];
            break;
        }
    }
    echo $campos;
}
?>
