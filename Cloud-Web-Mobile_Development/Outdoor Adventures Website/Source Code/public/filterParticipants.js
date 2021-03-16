function filterParticipants() {
	  //get the id of the price limit input
    let findTripInput = document.getElementById('find-participants').value

    window.location = '/participants/filter/' + parseInt(findTripInput)
    return false;
}
