//
// Created by shurj on 29-Sep-2024.
//

#include "CanvasItemDequeue.h"

CanvasItemDequeue::CanvasItemDequeue() {

}

const Vertex *CanvasItemDequeue::Enqueue(Vertex vertex) {
    m_vertices.push_back(vertex);
    return nullptr;
}

int CanvasItemDequeue::Dequeue() {
    return 0;
}

const CanvasItemDequeue::VertexNode *CanvasItemDequeue::Front() {
    return nullptr;
}

const CanvasItemDequeue::VertexNode *CanvasItemDequeue::Back() {
    return nullptr;
}

const Vertex *CanvasItemDequeue::GetBuffer() {
    return nullptr;
}
