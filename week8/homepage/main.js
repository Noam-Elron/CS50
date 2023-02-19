const root = document.querySelector(':root');
const orig_color_1 = root.style.getPropertyValue("--linear1");
const orig_color_2 = root.style.getPropertyValue("--linear1");
let counter = 0

function changeGradient() {
    if (counter % 2 == 1) {
    root.style.setProperty('--linear1', '#f44336');
    root.style.setProperty("--linear2", "#ffbe0b");
    }
    else {
    root.style.setProperty('--linear1', orig_color_1);
    root.style.setProperty("--linear2", orig_color_2);
    }
    counter++;
}

let button = document.querySelector("#colorButton");

button.addEventListener('click', changeGradient);
