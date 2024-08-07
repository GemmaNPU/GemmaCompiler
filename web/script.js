function loadHexFile( file ) {
    var fr = new FileReader();
    fr.onloadend = function () {
        var result = this.result;
        var rawBytes = new Uint8Array(result);
        var hex = "";
        for (var i = 0; i < this.result.byteLength; i++) {
            var byteStr = rawBytes[i].toString(16);
            if (byteStr.length < 2) {
                byteStr = "0" + byteStr;
            }
            hex += "" + byteStr;
        }

        Program.fromHex(hex)
                .show()

        document.getElementById('file-upload-dialog').close()
    };
    fr.readAsArrayBuffer(file)
}

function loadTextFile( file ){
    var fr = new FileReader();
    fr.onloadend = function () {
        var result = this.result;
        Program.fromText( result )
                .show()

        document.getElementById('file-upload-dialog').close()
    };
    fr.readAsText( file );
}



var hexFileInput = document.getElementById("hex-file-input");
    hexFileInput.onchange = function () { 
        loadHexFile( this.files[0] )           
    ;
}

var textFileInput = document.getElementById("text-file-input");
    textFileInput.onchange = function () {            
        loadTextFile( this.files[0] )
}


const assemble = Module.cwrap("assemble", "string", ["string"]);
const textContainer = document.getElementById("text");
const hexContainer = document.getElementById("hex-text");
const addressContainer = document.getElementById("address-container");

class Program {
    constructor( map ){
        this.map = map;
    }

    static fromText( str ){
        let text = str.split('\n')
        let hex = text.filter(t => t != "")
                      .map( instruction => assemble(instruction) );
        let map = new Map();
        for(let i = 0; i < text.length; i++){
            map.set(i, {hex: hex[i], text: text[i], mnemonic: text[i].split(' ')[0]});
        }
        return new Program(map);
    }

    static fromHex( hex ){
        alert('Disassemler not implemented yet');
    }

    show( hexContainer = document.getElementById("hex-text"), 
          textContainer = document.getElementById("text"), 
          addressContainer = document.getElementById("address-container") )
    {
        hexContainer.innerHTML = '';
        textContainer.innerHTML = '';
        addressContainer.innerHTML = '';

        let addressCount = 0;
        this.map.forEach( (value, id) => {
            let blocks = [];
            let row = document.createElement('code');
                row.innerHTML = value.text;
                row.classList.add("instruction-row")
                row.id = "instruction-" + id;
                row.onmouseenter = function(){
                    blocks.forEach( block => block.classList.add('focus') )
                }
                row.onmouseleave = function(){
                    blocks.forEach( block => block.classList.remove('focus'))
                }
            textContainer.appendChild( row );

            let hexParts = value.hex.match(/[\S]{8}/g) || [];
            addressCount += hexParts.length;
            hexParts.forEach( part => {
                let block = document.createElement('code');
                    block.onmouseenter = function(){
                        let scroll = row.offsetTop;
                        textContainer.scrollTo({top: scroll + 5, behavior: 'smooth'});
                        row.classList.add('focus');
                        blocks.forEach( block => block.classList.add('focus'));
                    }
                    block.onmouseleave = function(){
                        blocks.forEach( block => block.classList.remove('focus') )
                        row.classList.remove('focus')
                    }
                    block.innerHTML = parseInt(part, 2).toString(16).padStart(2, '0');
                    block.classList.add('hex-value')
                    block.style.background = getColor( value.mnemonic )
                hexContainer.appendChild( block );
                blocks.push( block );
                }); 
        });
        for(let i = 0; i < addressCount; i += 16 ){
            let address = document.createElement('div');
                address.innerHTML = '0x' + ("0000000" + i.toString(16)).substr(-8)
            addressContainer.appendChild( address );
        }
    }

}
window.Program = Program;

function getColor( str ){
    let colors = [
        '#4C6B1F',
        '#AE2E24',
        '#A54800',
        '#216E4E',
        '#206A83',
        '#943D73',
        '#0055CC'
    ]
    let hash = 0;
    str.split('').forEach(char => {
        hash = char.charCodeAt(0) + ((hash << 5) - hash)
    })
    return colors[hash % colors.length]
    // let colour = '#'
    // for (let i = 0; i < 3; i++) {
    //     const value = (hash >> (i * 8)) & 0xff
    //     colour += value.toString(16).padStart(2, '0')
    // }
    // return colour
}

window.dropTextHandler = function(ev) {
    console.log("File(s) dropped");
  
    // Prevent default behavior (Prevent file from being opened)
    ev.preventDefault();
  
    if (ev.dataTransfer.items) {
      // Use DataTransferItemList interface to access the file(s)
      [...ev.dataTransfer.items].forEach((item, i) => {
        // If dropped items aren't files, reject them
        if (item.kind === "file") {
          const file = item.getAsFile();
          loadTextFile( file  )
        }
      });
    } else {
      // Use DataTransfer interface to access the file(s)
      [...ev.dataTransfer.files].forEach((file, i) => {
        loadTextFile( file )
      });
    }
}
  
window.dropHexHandler = function(ev) {
    console.log("File(s) dropped");

    // Prevent default behavior (Prevent file from being opened)
    ev.preventDefault();

    if (ev.dataTransfer.items) {
        // Use DataTransferItemList interface to access the file(s)
        [...ev.dataTransfer.items].forEach((item, i) => {
        // If dropped items aren't files, reject them
        if (item.kind === "file") {
            const file = item.getAsFile();
            loadHexFile( file );
        }
        });
    } else {
        // Use DataTransfer interface to access the file(s)
        [...ev.dataTransfer.files].forEach((file, i) => {
            loadHexFile( file )
        });
    }
}
  
window.dragOverHandler = function(ev) {
    console.log("File(s) in drop zone");
  
    // Prevent default behavior (Prevent file from being opened)
    ev.preventDefault();
  }
  

document.getElementById('submit-bug').addEventListener( 'click' , (event) => {
    const moreData = document.getElementById('bug-more-data-checkbox').checked;
    const remoteUrl = '/bug-reports'
    let data = {
        msg: document.getElementById('bug-description-textarea').value.trim(),
        text: moreData ? document.getElementById('text').innerText : null,
        hex: moreData ? document.getElementById('hex-text').innerText : null,
    };
    fetch(remoteUrl, {
        method: "POST",
        body: JSON.stringify(data)
    }).then( () => {
        alert('Thanks')
    }).catch( (error) => {
        console.log( error );
        alert('Cannot deliver the bug report becuase of an error. Please try again. [You can report also this one :)]. Reason: ' + error)
    });
    
})