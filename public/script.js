var input = [
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
];

const arch = document.getElementById('select-arch');
var train_test;

// function resetTestInput() {
//     let cells = document.getElementsByClassName('cells');

//     for(let i = 0; i < cells.length; i++) {
//         cells[i].textContent = '-';
//         cells[i].style.fontWeight = 'normal';
//         cells[i].style.backgroundColor = 'white';
//         cells[i].removeEventListener('click');
//     }
// }

function initializeTestInput() {
    let cells = document.getElementsByClassName('cells');
    for(let i = 0; i < cells.length; i++) {
        cells[i].textContent = '-1';
        cells[i].style.fontWeight = 'normal';
        cells[i].style.backgroundColor = 'white';
        input[i] = -1;
    }
    for(let i = 0; i < cells.length; i++) {
        cells[i].addEventListener('click', () => {
            if(cells[i].textContent === '-1') {
                cells[i].textContent = '1';
                cells[i].style.backgroundColor = 'yellow';
                cells[i].style.fontWeight = 'bold';
                input[i] = 1;
            }
            else {
                cells[i].textContent = '-1';
                cells[i].style.backgroundColor = 'white';
                cells[i].style.fontWeight = 'normal';
                input[i] = -1;
            }
        });
    }
}

async function train() {
    try {
        let url = 'http://localhost:3000/train';
        if(arch.checked) {
            train_test = ['train_2', 'test_2'];
        } else {
            train_test = ['train', 'test'];
        }

        url += `?train_test=${encodeURIComponent(JSON.stringify(train_test))}`;

        const response = await fetch(url);
        const result = await response.text();

        initializeTestInput();

        document.getElementById('result').style.visibility = 'visible';
        document.getElementById('result').innerHTML = '<h2>NEURÔNIOS TREINADOS</h2>';
        document.getElementById('weights').style.visibility = 'visible';
        document.getElementById('weights').innerHTML = result;
        document.getElementById('test-btn').style.visibility = 'visible';
    }
    catch(error) {
        console.error(`Erro: ${error}`);
    }
}

async function sendInput() {
    if(arch.checked) {
        train_test = ['train_2', 'test_2'];
    } else {
        train_test = ['train', 'test'];
    }

    await fetch('http://localhost:3000/input', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ input, train_test })
    })
    .then(response => response.text())
    .then(data => {
        // Exibe a saída do programa em C na div 'output'
        document.getElementById('result').innerHTML = data;
    });
}





