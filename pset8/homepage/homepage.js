document.addEventListener('DOMContentLoaded', function() {

    let cat_pic = document.getElementById("cat_img");
    cat_pic.addEventListener("mouseover", (event) => {

        cat_pic.style.filter= "invert(100%)";
        setTimeout(() => {
            cat_pic.style.filter= "";
        }, 500);

        console.log("hovering");


        }, false);




    });


    //document.querySelector('#cat_img').addEventListener('mouseover', function() {
        //console.log("hovering");
        //let cat = document.querySelector('#cat_img');
        //cat.

    //});

