document.addEventListener('DOMContentLoaded', function() {

    // for multiple choice correct question
    let correct = document.querySelector('.correct');
    correct.addEventListener('click',function() {
        correct.style.backgroundColor = 'green';
        document.querySelector('#q1feedback').innerHTML = 'Correct!'
    });

    // for multiple choice incorrect questions
    let incorrects = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function() {
            incorrects[i].style.backgroundColor = 'red';
            document.querySelector('#q1feedback').innerHTML = 'Incorrect!';
        });
    }

    document.querySelector('#check').addEventListener('click', function() {
        let input = document.querySelector('input');
        if(input.value === "CS50") {
            input.style.backgroundColor = 'green';
            document.querySelector('#q2feedback').innerHTML = 'Correct!';
        }
        else {
            input.style.backgroundColor = 'red';
            document.querySelector('#q2feedback').innerHTML = 'Incorrect';
        }
    });
});