var MYAPI = function TIV3213(){
  var imgArray = new Array();
  var i = 0;
  var latlon = new Array(4);
  for (var i = 0; i < 4; i++) {
    latlon[i] = new Array(2);
  }

  function initMap(index) {

    var lon;
    var lat;
    var img = document.getElementById(index);

    if(latlon[index][1] != undefined && latlon[index][2] != undefined){
      var uluru = {lat:latlon[index][1], lng:latlon[index][2]};
      var map = new google.maps.Map(document.getElementById('map'), {
        zoom: 4,
        center: uluru
      });
      var marker = new google.maps.Marker({
        position: uluru,
        map: map
      });
    }else{
      EXIF.getData(img, function() {

        lon = toDecimal(EXIF.getTag(this, 'GPSLongitude'));
        lat = toDecimal(EXIF.getTag(this, 'GPSLatitude'));
        latlon[index][1] = lat;
        latlon[index][2] = lon;


        console.log("latlon[index][1],latlon[index][2] = "+latlon[index][1]+", "+latlon[index][2]);
        console.log("lat,lon = "+lat+", "+lon);

        var uluru = {lat:latlon[index][1], lng:latlon[index][2]};
        var map = new google.maps.Map(document.getElementById('map'), {
          zoom: 4,
          center: uluru
        });
        var marker = new google.maps.Marker({
          position: uluru,
          map: map
        });
      });
    }

  }

  var toDecimal = function(number) {
    return number[0].numerator + number[1].numerator / (60 * number[1].denominator) +
    number[2].numerator / (3600 * number[2].denominator);
  };

  function internalLoadImages(){
    console.log("internalLoadImages");

    var files = document.getElementById("images").files;

    for (var i = 0; i < files.length; i++) {
      var file = files[i];
      if (file.type.match('image.*')) {
        console.log("Ιs an image.");
        imgArray.push(file);
      } else {
        console.log("Ιs not an image.");
      }
    }

  }

  function internalShowLoadedImages(elem){
    console.log("internalshowLoadedImages");

    for (var i = 0; i < imgArray.length; i++) {

      var reader = new FileReader();
      reader.onload = (function(file) {

        var index = i;
        var imgArrayIn = imgArray;
        return function(e) {

          var span = document.createElement('figure');
          span.innerHTML = ['<img  src="', imgArrayIn[index].webkitRelativePath,
          '" onclick="loadImageWithInfo(',index,',\'',elem,'\')"/>','<figcaption>',
          escape(imgArrayIn[index].name), ' </figcaption>'].join('');
          document.getElementById(elem).insertBefore(span, null);

        }
      })(imgArray[i]);
      reader.readAsDataURL(imgArray[i]);

    }
  }

  function internalShowImage(index,elem){
    console.log("internalShowImage");
    //erase whatever is inside
    console.log("i is = "+i);
    if(i != 0){
      var eraser = document.getElementById(elem);
      eraser.removeChild(eraser.lastChild);
    }i=1;

    var span = document.createElement('div');
    span.innerHTML = ['<img  src="', imgArray[index].webkitRelativePath,
    '" id="',index,'" /> ','<pre id="allMetaDataSpan"></pre><br/>'].join('');
    document.getElementById(elem).insertBefore(span, null);
    //calling info getexif
  }

  function internalShowImageDetailedExifInfo(index,elem){
    console.log("internalShowImageDetailedExifInfo");

    //erase whatever is inside
    var eraser = document.getElementById(elem);

    while(eraser.firstChild){
      eraser.removeChild(eraser.firstChild);
    }

    var img = document.getElementById(index);

    EXIF.getData(img, function() {
      var allMetaData = EXIF.getAllTags(this);
      var allMetaDataSpan = document.getElementById(elem);
      allMetaDataSpan.innerHTML = JSON.stringify(allMetaData, null, "\t");
    });
  }

  function internalShowImageDetailedExifWithMap(index,elem){
    console.log("internalShowImageDetailedExifWithMap");

    //erase whatever is inside
  	var eraser = document.getElementById('maps');
  	eraser.removeChild(eraser.firstChild);

  	var span = document.createElement('div');
  	span.innerHTML = ['<h3 id="h3"></h3><div id="map"></div>'].join('');
  	document.getElementById(elem).insertBefore(span, null);

  	initMap(index);
  }

  return{
    loadImages: function(){
      internalLoadImages();
    },
    getLoadedImages: function(){
      return imgArray;
    },
    showLoadedImages: function(elem){
      internalShowLoadedImages(elem);
    },
    showImage: function(index,elem){
      internalShowImage(index,elem);
    },
    showImageDetailedExifInfo: function(index,elem){
      internalShowImageDetailedExifInfo(index,elem);
    },
    showImageDetailedExifWithMap: function(index,elem){
      internalShowImageDetailedExifWithMap(index,elem);
    }
  };

}();

function exec(){
  MYAPI.loadImages();
  MYAPI.getLoadedImages();
  MYAPI.showLoadedImages('allimages');
}

function loadImageWithInfo(index,elem){
  MYAPI.showImage(index,'bigimages');
  MYAPI.showImageDetailedExifWithMap(index,'maps');
  MYAPI.showImageDetailedExifInfo(index,'info');
}
