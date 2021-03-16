function filterTripsUpdate() {
	  //get the id of the price limit input
    let findTripInput = document.getElementById('find-trip').value

    window.location = '/admin/update/' + parseInt(findTripInput)
    return false;
}
