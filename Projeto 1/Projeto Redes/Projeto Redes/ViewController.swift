//
//  ViewController.swift
//  Projeto Redes
//
//  Created by Leonardo Maffei on 02/05/17.
//  Copyright © 2017 LeonardoMaffei. All rights reserved.
//

import UIKit
import SwiftSocket

class ViewController: UIViewController {

    @IBOutlet weak var SendButton: UIButton!
    @IBOutlet weak var conectionLabel: UILabel!
    
    
    let client = TCPClient(address: "192.168.223.88", port: 5000)

    
    override func viewDidLoad() {
        super.viewDidLoad()
    
        // Do any additional setup after loading the view, typically from a nib.
        
        
        switch client.connect(timeout: 10) {
        case .success:
            print("Sucesso na conexão")
            conectionLabel.text = "Conectado"
            
            break
        // Connection successful 🎉
        case .failure(let error):
            
            print("falha ao conectar ao cliente")
            conectionLabel.text = "Falha ao conectar"

            break
            // 💩
        }
    }
    
    @IBAction func sendData(_ sender: Any) {
        switch client.send(string: "Teste de envio" ){
        case .success:
            print("mensagem enviada")
        case .failure(let error):
            print("erro no envio")
        }
    }
    
    


    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

