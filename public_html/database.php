<?php
session_start();
?>
<html>
<head> <title> MariaDB </title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script> 
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
</head>
<body>

<script>
function applyStyle(){
    $("tr:odd").css("background-color", "#DCDCDC");
    $("tr.first").css("background-color", "#6495ED");
}
</script>

<script>
function sendDoubleAJAX(query, name, id, input, field){
    sendAJAX(query, name, id, input, field);
//    var id2 = id + "_buttons";
//    console.log(id2);
    sendAJAX("buttons", name, "select_buttons");
}
function sendAJAX(query, name, id, input = "empty", field){
    var xhttp;
    if (window.XMLHttpRequest){
        xhttp = new XMLHttpRequest();
    } else {
    xhttp = new ActiveXObject("Microsft.XMLHTTP");
    }
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200){
            document.getElementById(id).innerHTML= this.responseText;
        applyStyle();
        }
    }
    xhttp.open("POST", 
               "script.php?query="+query+
                          "&name="+name+
                          "&input="+input+
                          "&campo="+field,
               true);
    xhttp.send();
}

function fetchKey(event, field, tab_name, id){
    console.log(event.keyCode);
    console.log(id);
    sendAJAX("search", tab_name, "select", event.keyCode, field);
    var form = $("#"+id).val();    //fetch current form value

    if (event.keyCode == 8){       //backspace
        form.length = form.length - 1;
    }
    else if (event.keyCode == 13 || event.keyCode == 27){ 
                       //newline || escape
        form = "";    
    }
    $("#"+id).val(form);           //update form
}

function fetchInput(tab_name, fields, query_type, HTMLelement){
    split_fields = fields.split(",");
    console.log(split_fields);
    length = split_fields.length - 1;
    var forms = [];
    for (var i = 0; i < length; i++){
        forms[i]=tab_name+"_"+split_fields[i];
    }
    console.log(forms);
    var input_string = "";
    for (var i = 0; i < length; i++){
        var word = document.getElementById(forms[i]).value;
        input_string = "'" + word + "'" + "," + input_string;
    }
    length = input_string.length; 
    input_string= input_string.slice(0, length - 1);
    console.log(input_string);
     
    sendDoubleAJAX(query_type, tab_name, HTMLelement, input_string);
}


function debugAJAX(query, name){
    var xhttp;
    if (window.XMLHttpRequest){
        xhttp = new XMLHttpRequest();
    } else {
    xhttp = new ActiveXObject("Microsft.XMLHTTP");
    }
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200){
            document.getElementById("debug").value= this.responseText;
        applyStyle();
        }
    }
    xhttp.open("POST", "script.php?query="+query+"&name="+name, true);
    xhttp.send();
}
    
</script>

<script>
$(document).ready(function(){
    applyStyle();
});
</script>

<?php


include 'functions.php';


$servername = "localhost";
$username = test_input($_POST["username"]);
$password = test_input($_POST["password"]);
$database = test_input($_POST["database"]);
$connection = mysqli_connect($servername, $username, $password, $database);

$_SESSION["username"]=$username;
$_SESSION["password"]=$password;
$_SESSION["database"]=$database;
$_SESSION["servername"]=$servername;
$_SESSION["connection"]=$connection;


if (!$connection){
    die("Connection failed " . mysqli_connect_error());
}
echo "Connected sucessfully. <br><br>";

$sql = "show databases";
$result = mysqli_query($connection, $sql);
printResult($result, $connection);
$db_names=fetchDBNames($result);

$query="tables";

dropdown_button($query, $db_names, "tables");

echo "
<button> Create LibraryDB </button>
<button> Create EmptyDB   </button>
";

mysqli_close($connection);

echo "<p id='tables'>";
echo "<p id='select'>";
echo "<p id='select_buttons'>";
echo "<p id='debug'>";

?>

</body>
</html>
