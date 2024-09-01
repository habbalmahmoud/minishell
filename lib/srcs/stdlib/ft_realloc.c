void	*ft_realloc(void* ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;
    if (new_size == 0)
	{
		free(ptr);
		return (NULL);
    }

    // If the pointer is NULL, simply allocate new memory
    if (ptr == NULL) {
        return malloc(new_size);
    }

    // Retrieve the size of the current block (assuming we have some way to get it)
    // For a real implementation, you would need to manage metadata about allocations
    size_t old_size = /* function to get size of allocated memory block */;
    
    // Allocate a new memory block with the requested size
    void* new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;  // Allocation failed
    }

    // Copy the old data to the new memory block
    // Note: Check if the old size is less than new size to avoid reading beyond the old block
    size_t copy_size = old_size < new_size ? old_size : new_size;
    memcpy(new_ptr, ptr, copy_size);

    // Free the old memory block
    free(ptr);

    return new_ptr;
}
