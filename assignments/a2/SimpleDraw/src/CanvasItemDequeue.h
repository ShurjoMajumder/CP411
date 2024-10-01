//
// Created by shurj on 29-Sep-2024.
//

#ifndef SHAPES_CANVASITEMDEQUEUE_H
#define SHAPES_CANVASITEMDEQUEUE_H

#include <memory>
#include <vector>
#include "CanvasItem.h"


class CanvasItemDequeue {
private:
    struct CanvasItemNode {
        const CanvasItem *item;
        CanvasItemNode *prev;
        CanvasItemNode *next;
    };

    std::vector<CanvasItemNode> m_canvasItems;
    CanvasItemNode *m_front;
    CanvasItemNode *m_back;

public:
    CanvasItemDequeue();

    const CanvasItem* Enqueue(CanvasItem&);
    const CanvasItem* Dequeue();
    const CanvasItem* PopAt(int);

    const CanvasItemNode *Front() const;
    const CanvasItemNode *Back() const;
    size_t Length() const;

    const Vertex *GetBuffer() const;
};


#endif //SHAPES_CANVASITEMDEQUEUE_H
