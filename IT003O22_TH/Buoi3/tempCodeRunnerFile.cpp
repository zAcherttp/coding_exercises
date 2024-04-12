    SinglyLinkedListNode* current = head;
    SinglyLinkedListNode* element = new SinglyLinkedListNode(x);

    if(current->next->data > x)
    {
        element->next = head;
        head = element;
        return head;
    }
    while(current != nullptr)
    {
        if(current->next->data > x)
        {
            element->next = current->next;
            current->next = element;
            return head;
        }
        current = current->next;
    }
    if(current == nullptr && current->data < x)
    {
        current->next = element;
    }
    return head;