//
// Created by shurj on 29-Sep-2024.
//

#include "CanvasItemDequeue.h"

CanvasItemDequeue::CanvasItemDequeue() {

}

const CanvasItem *CanvasItemDequeue::Enqueue(CanvasItem &canvasItem) {
//    m_canvasItems.push_back(canvasItem);
    auto *item = new CanvasItem(canvasItem);
    auto n = CanvasItemNode(item, m_back, nullptr);
    m_canvasItems.push_back(n);
    m_back->next = &m_canvasItems.back();
    m_back = &m_canvasItems.back();

    return m_back->item;
}

const CanvasItem *CanvasItemDequeue::Dequeue() {
    return nullptr;
}

const CanvasItem *CanvasItemDequeue::PopAt(int) {
    return nullptr;
}

const CanvasItemDequeue::CanvasItemNode *CanvasItemDequeue::Front() const {
    return nullptr;
}

const CanvasItemDequeue::CanvasItemNode *CanvasItemDequeue::Back() const {
    return nullptr;
}

size_t CanvasItemDequeue::Length() const {
    return m_canvasItems.size();
}

const Vertex *CanvasItemDequeue::GetBuffer() const {
    return nullptr;
}

