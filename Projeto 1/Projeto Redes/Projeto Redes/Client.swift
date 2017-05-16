//
//  Client.swift
//  Projeto Redes
//
//  Created by Erich Silveira on 15/05/17.
//  Copyright © 2017 LeonardoMaffei. All rights reserved.
//

import UIKit
import SwiftSocket

class Client: NSObject {

    
    static var sharedInstance = Client()
    
    
    var client = TCPClient(address: "192.168.1.100", port: 5000)
    
    
    
    func setupClient(ip: String, port: Int32){
        
        self.client = TCPClient(address: ip, port: port)
        
        
    }
    
}
