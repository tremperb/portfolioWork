function updateMenu(uID) {
  $.ajax({
    url: '/menu/' + uID,
    type: 'PUT',
    data: $('#update-menu').serialize(),
    success: function(result) {
      window.location = '/menu/' + uID;
    }
  })

  return false;
}

function textHighlight() {

  var highlights = document.getElementsByClassName("highlight");

  var text = document.getElementById("output-text").innerHTML;
  console.log(highlights[0].value);
  console.log(text);

  var highlightCount = 0;
  var result = '';
  var spaceCount = 0;
  for(var i = 0; i < text.length; i++) {
    let char = text.charCodeAt(i);

    if(char == 32) {
      console.log("space: ", text.charAt(i));
      var holder = text.charAt(i);
      result += holder;
      spaceCount++;
    }
    else if(char == 10 || char == 9) {
      var holder = '<br>';
      result += holder;
    }
    else if(char == 46) {

      console.log("period: ", text.charAt(i));
      var holder= text.charAt(i) + '<br>';
      result += holder;
      highlightCount++;
      spaceCount = 0;
    }
    else {

      console.log("letter: ", text.charAt(i), text.charCodeAt(i));
      var color = highlights[highlightCount].value;
      if(color == 'blue') {
        color = 'lightblue';
      }
      var holder= '<mark style="background-color:' +  color + ';">' + text.charAt(i) + '</mark>';
      result += holder;
      spaceCount = 0;
    }


    //Reset highlight counter
    if(highlightCount == 3) {
      highlightCount = 0;
    }
  }

  document.getElementById("output-text").innerHTML = result;
}


function updateFont() {

  var selectedFont = document.getElementById("fontOne").value;
  console.log("Selected Font: ", selectedFont)
  var item = document.getElementById("output-text");
  if(selectedFont == "Open Dyslexic") {
    item.style.fontFamily = "open-dyslexic";
  }
  else {
    item.style.fontFamily = "comic-sans";
  }
}

$(document).ready(function() {

  var elementExists = document.getElementById("output-text");
  if(elementExists) {
    updateFont();
    textHighlight();
    //call other functions here
  }

});

function say() {
    var msg = new SpeechSynthesisUtterance();
    var voices = window.speechSynthesis.getVoices();
    msg.voice = voices[10];
    msg.voiceURI = "native";
    msg.volume = 1;
    msg.rate = 1;
    msg.pitch = 1;
    msg.text = document.getElementsByName("message")[0].value;
    msg.lang = 'en-US';
    speechSynthesis.speak(msg);
}
