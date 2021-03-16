function deleteParticipant(tid, pid){

    $.ajax({
        url: '/participants/delete/tid/' + tid + '/pid/' + pid,
        type: 'DELETE',
        success: function(result){
            window.location.reload(true);
        }
    })
};
