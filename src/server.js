const express   = require('express');
const cors      = require('cors');
const { spawn } = require('child_process');

const app = express();
const PORT = 3000;

app.use(cors()); // Adicione esta linha para habilitar o CORS para todas as origens

app.use(express.json());

app.get('/train', (_, res) => {
    const process = spawn('src/train.exe');

    let result = '';
    process.stdout.on('data', data => {
        result += data.toString();
    });

    process.stderr.on('data', data => {
        console.error(`Error: ${data}`);
    });

    process.on('close', code => {
        console.log(`Processo terminado com código ${code}`);
        console.log(`-> ${result}`);
        res.send(result);
    })
});

app.post('/input', (req, res) => {
    const input = req.body.input.flat();
    const process = spawn('src/test.exe', ['['+input.join(',')+']']);

    let result = '';
    process.stdout.on('data', data => {
        result += data.toString();
    });
    
    process.stderr.on('data', data => {
        console.error(`Error: ${data}`);
    });

    process.on('close', code => {
        console.log(`Child process exited with code ${code}`);
        console.log(`--> ${result}`);
        res.send(result);
    });
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
