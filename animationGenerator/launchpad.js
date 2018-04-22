var frameCount = 1;

var matrices = [];

$(document).ready(function() {

  $cell = $("td");
  var $size = $('input[name="size"]').val();

  $(document).on('mouseenter', 'td', function() {
    $(this).fadeTo('fast', 0.7);
  });

  $(document).on('mouseleave', 'td', function() {
    $(this).fadeTo('fast', 1);
  });

  $(document).on('click', '#left', function(e) {
    if (frameCount != 1) {
      matrices[frameCount - 1] = getGrid(8);

      frameCount--;

      uploadGrid();

      document.querySelector("#frameCount").innerHTML = frameCount + " of 8";
    }
  })

  $(document).on('click', '#right', function(e) {
    if (frameCount != 8) {
      matrices[frameCount - 1] = getGrid(8);

      frameCount++;

      uploadGrid();

      document.querySelector("#frameCount").innerHTML = frameCount + " of 8";
    }
  })

  // Click to toggle cell state
  $(document).on('click', 'td', function() {
    if ( $(this).hasClass('live') ) {
      $(this).removeClass('live');
      $(this).addClass('dead');
    } else if ( $(this).hasClass('dead') ) {
      $(this).removeClass('dead');
      $(this).addClass('live');
    } else {
      $(this).addClass('live');
    }

    matrices[frameCount - 1] = getGrid(8);
  });

  // Submit form
  $(document).on('click', 'input[name="make_grid"]', function() {
    $("#grid").remove();
    $size = $('input[name="size"]').val();
    $("body").append( makeGrid($size) );
    $sizeText.text("size: " + $size + "x" + $size);
  });

  // Make grid
  var makeGrid = function(size) {
    // grid to return
    var $rtnGrid = $('<table id="grid"></table>');
    for (r=0; r<size; r++) {
      var $row = $('<tr></tr>');
      for (c=0; c<size; c++) {
        $row.append( $('<td></td>') );
      }
      $rtnGrid.append($row);
    }
    return $rtnGrid;
  }

  var getGrid = function() {
    var $matrix = [];
    for (var i = 0; i < 8; i++) {
      var $row = [];
      var row = document.querySelectorAll("tr")[i];
      for (var j = 0; j < 8; j++) {
        var $col = row.querySelectorAll("td")[j].className;
        $row.push($col);
      }
      $matrix.push($row);
    }

    return $matrix;
  }

  var uploadGrid = function() {
    for (var i = 0; i < 8; i++) {
      var row = document.querySelectorAll("tr")[i];
      for (var j = 0; j < 8; j++) {
        if (matrices[frameCount - 1]) {
          row.querySelectorAll("td")[j].className = matrices[frameCount - 1][i][j];
        } else {
          row.querySelectorAll("td")[j].className = "";
        }
      }
    }
  }

  $(document).on('click', '#export', function(e) {


    var $matrixFrame = [];

    for (var i = 0; i < 8; i++) { // Each frameCount
      var bytes = [];
      for (var j = 0; j < 8; j++) { // Each row
        var $value = 0;
        for (var k = 0; k < 8; k++) { // Each column
          if (matrices[i][j][k] == "live") {
            $value += Math.pow(2, 7 - k);
          }
        }
        bytes.push($value);
      }
      $matrixFrame.push(bytes);
    }

    var html = `<p id = "left">
  void ` + document.querySelector("input").value + ` (int aniStep, int keysId){<br>
<br>
    var rowMatrix = ` + JSON.stringify($matrixFrame) + `;<br>
<br>
    for (var i = 0; i < 8; i++) {<br>
      lc.setRow(0, i, rowMatrix[aniStep][i]);<br>
    }<br>
<br>
    steps[keysId] += 1;<br>
<br>
    if (aniStep == 8) {<br>
      keys[keysId] = '0';<br>
      steps[keysId] = 0;<br>
    }<br>
<br>
  }<br>
  </p>
    `;

    console.log(document.querySelector("#exportSpace"));
    document.querySelector("#exportSpace").innerHTML = html;
  })

});
