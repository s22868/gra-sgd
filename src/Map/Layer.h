//
// Created by Mateusz on 07.05.2023.
//

#ifndef GRASGD_LAYER_H
#define GRASGD_LAYER_H

class Layer {
public:
    virtual void Render()=0;
    virtual void Update()=0;

private:

};

#endif //GRASGD_LAYER_H
