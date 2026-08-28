/**
 * @file lag_window.h
 * @brief Window management structures and functions for the LAG library.
 */

#ifndef LAG_WINDOW_H
# define LAG_WINDOW_H

# include <ncurses.h>
# include <sys/ioctl.h>
# include <strings.h>

/**
 * @enum e_lag_window_flags
 * @brief Configuration flags controlling window behavior and scaling.
 */
typedef enum e_lag_window_flags {
    IS_FULLSCREEN = 1, /**< Expand window to cover full terminal dimensions. */
    IS_RESIZABLE  = 2  /**< Calculate aspect ratios to support dynamic scaling. */
} lag_window_flags;

/**
 * @struct s_lag_window_infos
 * @brief Setup parameters for creating a LAG window handle.
 */
typedef struct s_lag_window_infos {
    unsigned int        width;  /**< Initial window width in columns. */
    unsigned int        height; /**< Initial window height in rows. */
    unsigned int        row;    /**< Top-left Y starting position. */
    unsigned int        col;    /**< Top-left X starting position. */
    lag_window_flags    flags;  /**< Bitwise flags for window characteristics. */
} lag_window_infos;

/**
 * @struct s_lag_window
 * @brief Active window instance holding the ncurses handle and scale ratios.
 */
typedef struct s_lag_window {
    WINDOW              *win;     /**< Pointer to the underlying ncurses WINDOW structure. */
    lag_window_infos    *infos;   /**< Configuration options associated with this window. */
    float               w_ratio;  /**< Width ratio relative to terminal bounds (0.0 to 1.0). */
    float               h_ratio;  /**< Height ratio relative to terminal bounds (0.0 to 1.0). */
} lag_window;

/**
 * @brief Initializes a new LAG window structure and creates its ncurses handle.
 *
 * Evaluates screen boundaries, sets scaling ratios if resizable, and allocates
 * the underlying ncurses window instance.
 *
 * @param[out] win       Pointer to the window structure to initialize.
 * @param[in,out] win_infos Configuration parameters (bounds auto-corrected if invalid).
 */
void lag_create_window(lag_window *win, lag_window_infos *win_infos);

/**
 * @brief Clears, refreshes, and deletes an active LAG window handle.
 *
 * @param[in,out] win Pointer to the target window instance to free.
 */
void lag_destroy_window(lag_window *win);

/**
 * @brief Recalculates window dimensions based on stored scaling ratios and updates the buffer size.
 *
 * @param[in,out] win Pointer to the resizable window instance.
 */
void lag_autoresize_window(lag_window *win);

/**
 * @brief Explicitly resizes a LAG window to new dimensions.
 *
 * Checks input parameters against max terminal dimensions before resizing the ncurses window buffer.
 *
 * @param[in,out] win Pointer to the window instance to resize.
 * @param[in] width   Target width in columns.
 * @param[in] height  Target height in rows.
 * @return true if resizing succeeded, false if the ncurses buffer update failed.
 */
bool lag_resize_window(lag_window *win, unsigned int width, unsigned int height);

#endif /* LAG_WINDOW_H */
