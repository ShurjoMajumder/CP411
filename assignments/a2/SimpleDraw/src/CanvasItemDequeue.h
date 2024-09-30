//
// Created by shurj on 29-Sep-2024.
//

#ifndef SHAPES_CANVASITEMDEQUEUE_H
#define SHAPES_CANVASITEMDEQUEUE_H

#include <memory>
#include <vector>


struct Vertex {
    float x, y;
};

class CanvasItemDequeue {
private:
    typedef struct VertexNode {
        const Vertex *item;
        std::shared_ptr<Vertex> prev;
        std::shared_ptr<Vertex> next;
    } m_nodes;

    std::vector<Vertex> m_vertices;
    VertexNode *m_front, *m_back;

public:
    CanvasItemDequeue();

    const Vertex* Enqueue(Vertex);
    int Dequeue();

    const VertexNode *Front();
    const VertexNode *Back();

    const Vertex *GetBuffer();
};


#endif //SHAPES_CANVASITEMDEQUEUE_H
