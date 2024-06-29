#pragma once

class Field;

/**
 * Console displayer for game fields.
 */
class FieldDisplayer {
public:
    /**
     * Display the field with all the humanoids
     * @param field the field to display
     */
    static void display(Field& field);
};
