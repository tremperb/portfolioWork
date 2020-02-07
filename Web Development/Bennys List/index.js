/*
 * Write your JS code in this file.  Don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Brayden Tremper
 * Email: tremperb@oregonstate.edu
 */

/*Sell an item clicking*/
var sellSomethingButton = document.getElementById("sell-something-button");
var sellSomething = document.getElementById("sell-something-modal");
var sellBackdrop = document.getElementById("modal-backdrop");

sellSomethingButton.addEventListener('click', handleSell);

/*
 * Opens sell screen and backdrop
 */
function handleSell(event) {
  console.log("==Sell Something Button Clicked");
  sellBackdrop.style.display = "block";
  sellSomething.style.display = "block";
}

var closeOne = document.getElementById("modal-close");
var closeTwo = document.getElementById("modal-cancel");

closeOne.addEventListener('click', handleClose);
closeTwo.addEventListener('click', handleClose);

/*
 *  Handles close and resets all elements
 */
function handleClose(event) {
  console.log("==Closing Add Item Form");
  sellBackdrop.style.display = "none";
  sellSomething.style.display = "none";

  document.getElementById("post-text-input").value = "";
	document.getElementById("post-photo-input").value = "";
	document.getElementById("post-price-input").value = "";
	document.getElementById("post-city-input").value = "";
	document.getElementById("post-condition-new").checked = true;
}
/*End Sell clicking*/

/*Start Add New Item*/

/*
 * Get the condition
 */
function getCondition (object) {
//  var index = 0;
  var condition = document.getElementsByName(object);
  for(var i = 0; i < condition.length; i++) {
    if(condition[i].checked == true) {
      //index = i;
      return condition[i].value;
    }
  }

  return '';
}

/*
 * Extra Credi: Add new city to dropdown
 */
 function addDropItem (myCity) {
   var post = document.getElementsByClassName('post');
   var present = false;

   for(var j = 0; j < post.length; j++) {
     if(myCity.toLowerCase() == (post[j].dataset.city).toLowerCase()) {
         present = true;
     }
   }

   if(present == false) {
     var content = document.getElementById("filter-city");
     var option = document.createElement("option");
     option.text = myCity;
     content.add(option);
   }
 }

 /*
  * Add a new post
  */
function newContainer (url, title, price, city) {
  var photoContainer = document.getElementById("posts"); //initialize
  var post = document.createElement('div');
  post.classList.add('post');
  post.setAttribute("data-price", price);
  var cityDataOne = (city).slice(1);  //get rid of ( )
  var cityData = (cityDataOne).slice(0, -1);
  post.setAttribute("data-city", cityData);
  post.setAttribute("data-condition", getCondition('post-condition'));
  addDropItem (cityData);
/////////////////////////////////////////////////
  var newContent = document.createElement('div');
  newContent.classList.add('post-contents');
  post.appendChild(newContent);
//////////////////////////////////////////////////
  var newImg = document.createElement('div');
  newImg.classList.add('post-image-container');
  newContent.appendChild(newImg);
//////////////////////////////////////////////////
	var img = document.createElement('img');
  img.classList.add('src')
	img.src = url;
	newImg.appendChild(img);
//////////////////////////////////////////////////
  var getContent = document.createElement('div');
  getContent.classList.add('post-info-container');
  newContent.appendChild(getContent);
//////////////////////////////////////////////////
  var newTitle = document.createElement('a');
  newTitle.classList.add('post-title');
  newTitle.textContent = title;
  getContent.appendChild(newTitle);
//////////////////////////////////////////////////
  var newPrice = document.createElement('span');
  newPrice.classList.add('post-price');
  newPrice.textContent = price;
  getContent.appendChild(newPrice);
//////////////////////////////////////////////////
  var newCity = document.createElement('span');
  newCity.classList.add('post-city');
  newCity.textContent = city;
  getContent.appendChild(newCity);
//////////////////////////////////////////////////
  photoContainer.appendChild(post);
}


var addItem = document.getElementById("modal-accept");
addItem.addEventListener('click', handleAdd);

/*
 * Validates input for add to make sure everything is filled out
 */
function validateInput(url, title, price, city) {
  if((url && title && price && city) != "") {
    return true;
  }
  else {
    alert("You must fill out all required fields");
    return false;
  }
}

/*
 * Calls function to add as long as everything if filled
 */
function handleAdd(event) {
  console.log("==Adding New Item");
  var title = document.getElementById("post-text-input").value;
	var price = document.getElementById("post-price-input").value;
	var city = document.getElementById("post-city-input").value;
	var url = document.getElementById("post-photo-input").value;
  var filled = validateInput(url, title, price, city);

  if(filled == true) {
    newContainer(url, title, '$'+ price, '('+city+')');
    handleClose(event);
  }
}

var updateButton = document.getElementById("filter-update-button");
updateButton.addEventListener('click', findFilters);

/*
 * General call function to filter elements
 */
function findFilters (event) {
  console.log("Updating to fit these conditions:");
  var name = document.getElementById("filter-text").value;
  var minPrice = document.getElementById("filter-min-price").value;
  var maxPrice = document.getElementById("filter-max-price").value;
  var city = document.getElementById("filter-city").value;
  var condition = getCondition('filter-condition'); //need to fix if the enter more than one condition

  if (name != "") {
    console.log("Name:", name);
    filterName(name);
  }
  if (minPrice != "") {
    console.log("Min Price:", minPrice);
    filterPrice(minPrice, maxPrice, 1);
  }
  if (maxPrice != "") {
    console.log("Max Price:", maxPrice);
    filterPrice(minPrice, maxPrice, 2);
  }
  if (city != "") {
    console.log("City:", city);
    filterCity (city);
  }
  if (condition != "") {  //check if at least one is checked
    console.log("Condition:", condition);
    //need new function to get all conditions checked
    filterAllConditions();
  }
}

/*
 * Filters all conditions (allows for multiple to be clicked)
 */
function filterAllConditions () {
  var condition = document.getElementsByName('filter-condition');
  var data = document.getElementsByClassName('post');

  for(var i = 0; i < condition.length; i++) {
    if(condition[i].checked == false) {
      for(var j = 0; j < data.length; j++) {
        if(condition[i].value == data[j].dataset.condition) {
          removePost(j);
          j--;
        }
      }
    }
  }
}

/*
 * Filters by name of object
 */
function filterName(name) {
  var content = document.getElementsByClassName('post-title');
  for(var i = 0; i < content.length; i++) {
    if(((content[i].textContent).toLowerCase()).indexOf(name.toLowerCase()) < 0) {
      //call remove with index so you can remove thaat index and use same remove for every func
      removePost(i);
      i--;
    }
  }
}

/*
 * Filters by price. Two settings min and max
 */
function filterPrice(minPrice, maxPrice, type) {
  var content = document.getElementsByClassName('post-price');

  for(var i = 0; i < content.length; i++) {
    var newB = (content[i].textContent).slice(1); //get rid of $
    var asInt = parseInt(newB, 10);               //convert string to int
    if(type == 1) { // 1 indicates odd
      if(asInt < minPrice) {
        removePost(i);
        i--;
      }
    }

    else if(type == 2) {  // 2 indicates odd
      if(asInt > maxPrice) {
        removePost(i);
        i--;
      }
    }
  }
}

/*
 * Filters by City
 */
function filterCity (city) {
  var content = document.getElementsByClassName('post-city');
  var count = 1;
  var newCity = '(' + city + ')';
  for(var i = 0; i < content.length; i++) {
    if(newCity.toLowerCase() != (content[i].textContent).toLowerCase()) {
      removePost(i);
      i--;
    }
  }
}

/*
 * Removes post via the filters at index
 */
function removePost(index) {
  var noMatch = document.getElementsByClassName('post');
  noMatch[index].remove();
}
