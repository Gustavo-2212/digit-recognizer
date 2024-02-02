var input = [
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
];


function initializeTestInput() {
    const cells = document.getElementsByClassName('cells');
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
        const response = await fetch('http://localhost:3000/train');
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
    await fetch('http://localhost:3000/input', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ input })
    })
    .then(response => response.text())
    .then(data => {
        // Exibe a saída do programa em C na div 'output'
        document.getElementById('result').innerHTML = data;
    });
}
