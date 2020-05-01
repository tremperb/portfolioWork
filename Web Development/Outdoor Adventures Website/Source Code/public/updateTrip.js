function updateTrip(tid) {
  $.ajax({
    url: '/admin/update/' + tid,
    type: 'PUT',
    data: $('#update-trip').serialize(),
    success: function(result) {
      window.location = '/admin/update/'+tid;
    }
  })

  return false;
}
