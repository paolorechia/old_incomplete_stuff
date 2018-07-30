<?php
include 'functions.php';
session_start();
$pedido= test_input($_REQUEST['query']);
$nome  = test_input($_REQUEST['name']);
$input = test_input($_REQUEST["input"]);
$campo = test_input($_REQUEST["campo"]);


$servername = $_SESSION["servername"];
$username = $_SESSION["username"];
$password = $_SESSION["password"];
$database = $_SESSION["database"];

$connection = mysqli_connect($servername, $username, $password, $database);

if ($pedido == "tables"){
    mysqli_select_db($connection, $nome);
    $_SESSION["database"] = $nome;

    $sql = "show tables";
    $result = mysqli_query($connection, $sql);
    printResult($result, $connection);

    $tables=fetchTablesNames($result, $nome);
    $query="select";
    dropdown_button($query, $tables, "select");
    echo "
         <button> Create Table </button>
         <button> Remove Table </button>";
    
}
elseif ($pedido == "buttons"){
    $fields = $_SESSION["last_fields"];
    printButtons($nome, $connection, $fields);
}
elseif ($pedido == "select"){
    $fields = SelectTable($nome, $connection);
    $_SESSION["last_fields"]=$fields;
}
else if ($pedido == "insert"){
    echo "Insercao <br>";
    insereLinha($connection);
    $fields = SelectTable($_SESSION["current_table"], $connection);
    $_SESSION["last_fields"]=$fields;
}
else if ($pedido == "delete"){
    echo "Remocao <br>";
    removeLinha($connection);
    $fields = SelectTable($_SESSION["current_table"], $connection);
    $_SESSION["last_fields"]=$fields;
}
else if ($pedido == "update"){
    echo "Atualizando <br>";
    atualizaLinha($connection, $campo, $input, $nome);
    $fields = SelectTable($_SESSION["current_table"], $connection);
    $_SESSION["last_fields"]=$fields;
}
else if ($pedido == "search"){
//    $fields = SelectTable($_SESSION["current_table"], $connection);
//    printButtons($nome, $connection, $fields);
    $buffer = $_SESSION["buffer"];
    echo "<br>Busca <br>";
    $letra = chr($input);
    if ($input == 8){
        echo "backspace <br>";
        $length = strlen($buffer);
        $buffer = substr($buffer, 0, $length - 1);
    }
    else if ($input == 27){
        echo "escape <br>";
        $buffer="";
    }
    else{
        $buffer=$buffer . $letra;
    }
    if ($input == 13){
        echo "newline <br>"; 
        searchTable($_SESSION["current_table"], $campo, $buffer, $connection);
        $buffer="";
    }
    else{
        searchTable($_SESSION["current_table"], $campo, $buffer, $connection);
    }
    $_SESSION["buffer"] = $buffer ;
    echo $campo. "= " . $buffer;
    
}
?>
