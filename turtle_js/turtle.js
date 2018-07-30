var canvas = document.getElementById("turtle_canvas");
var ctx = canvas.getContext("2d");

var drawMovement = function(){
    ctx.beginPath();
    ctx.moveTo(turtle.x, turtle.y);
    if (turtle.mode == "down"){
        ctx.lineTo(turtle.movement.x, turtle.movement.y);
        ctx.stroke();
    }
    else {
        ctx.moveTo(turtle.movement.x, turtle.movement.y);
    }
}

var turtle = {
    x: 400,
    y: 300,
    mode: "up",
    setMode: function(mode){
        this.mode = mode;
    },
    movement: {
        x: 400,
        y: 300,
    },
    move: function(direction, amount){
            amount = parseInt(amount);
            console.log("I'm moving... " + direction);
            if      (direction == "W"){
                this.movement.x -= amount;
            }
            else if (direction == "N"){
                this.movement.y -= amount;
            }
            else if (direction == "E"){
                this.movement.x += amount;
                console.log(this.movement);
            }
            else if (direction == "S"){
                this.movement.y += amount;
            }
            else{
                console.log("Invalid direction... '" + direction + "'!"); 
            }
            drawMovement();
            this.x = this.movement.x;
            this.y = this.movement.y;
    },
};

var splitIntoLines = function(input, lines){
    var string = input;
    do {
        var end = string.search('\n');
        lines.push(string.substr(0, end));
        string = string.slice(end + 1, string.length);
        end = string.search('\n');
//        console.log(lines);
    }while (string != "");
}

var parseLines = function(lines){
    for (var i = 0; i < lines.length; i++){
        parseLine(lines[i]);
    }
}

var parseLine = function(line){
    if (line[0] == "D"){
        turtle.setMode("down");
    }
    else if (line[0] == "U"){
        turtle.setMode("up");
    }
    else{
        var space = line.search(" ");
        if (space < 0){
            console.log("Invalid syntax... '" + line[0] + "' ...skipping!");
        }
        else{
            turtle.move(line[0], line.slice(space, line.length));
        }
    }
}

var parseText = function(input){
    var queue = [];
    var lines = [];
    splitIntoLines(input, lines);
    parseLines(lines);
//    console.log(input[0]);
}

var openFile = function(event) {
    console.log("opening file...>");
    var input = event.target;
    var reader = new FileReader();
    reader.onload = function(){
        var text = reader.result;
        console.log(reader.result);
        parseText(text);
    }
    reader.readAsText(input.files[0]);
}
