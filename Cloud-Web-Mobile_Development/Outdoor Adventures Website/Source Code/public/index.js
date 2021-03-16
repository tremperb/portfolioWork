function getPackingList() {
  var checkbox = document.getElementById("myCheck");
  var listContainer = document.getElementById("taking-list");

  if(checkbox.checked == true) {
    listContainer.style.display = "block";
  }
  else {
    listContainer.style.display = "none";
  }
}
