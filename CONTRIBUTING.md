# Contributing to Sunset Rangers

Thank you for your interest in contributing to Sunset Rangers! This document provides guidelines for contributing to the project.

## Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally
3. **Install dependencies** (see QUICKSTART.md)
4. **Verify setup** by running `./verify.sh`

## Development Workflow

### Before Making Changes

1. Run tests to ensure everything works:
   ```bash
   ./test.sh
   ```

2. Create a new branch for your feature/fix:
   ```bash
   git checkout -b feature/your-feature-name
   ```

### Making Changes

1. **Follow the existing code style**
   - Use consistent indentation (spaces, not tabs)
   - Keep functions focused and small
   - Add comments for complex logic

2. **Test your changes**
   - Build the project: `make all`
   - Test functionality: `make run`
   - Run tests: `./test.sh`

3. **Keep commits focused**
   - One logical change per commit
   - Write clear commit messages

### Submitting Changes

1. **Push to your fork**:
   ```bash
   git push origin feature/your-feature-name
   ```

2. **Create a Pull Request** on GitHub
   - Describe what changes you made
   - Explain why the changes are needed
   - Reference any related issues

## Code Guidelines

### C Code Style

- Use C99 standard
- Follow existing naming conventions:
  - `PascalCase` for types/enums
  - `camelCase` for variables
  - `UPPER_CASE` for constants/macros
- Keep line length under 100 characters
- Add error checking for file operations

### Asset Guidelines

- **Images**: PNG format preferred
- **Fonts**: TrueType (.ttf) format
- Keep file sizes reasonable (optimize images)
- Place assets in appropriate directories:
  - `assets/` - Backgrounds
  - `character/` - Character sprites
  - `images/` - UI elements
  - `fonts/` - Font files

## What to Contribute

### Wanted Features

- [ ] Enemy AI and enemy sprites
- [ ] Multiple levels/stages
- [ ] Sound effects and background music
- [ ] Particle effects (dust, muzzle flash, etc.)
- [ ] Health/score display
- [ ] Settings menu (volume, controls, etc.)
- [ ] Gamepad support
- [ ] Save/load system
- [ ] Power-ups and collectibles

### Bug Fixes

Found a bug? Please:
1. Check if it's already reported in Issues
2. If not, create a new Issue with:
   - Clear description of the bug
   - Steps to reproduce
   - Expected vs actual behavior
   - Your system info (OS, compiler version)

### Documentation

Documentation improvements are always welcome:
- Fix typos
- Clarify installation steps
- Add troubleshooting tips
- Improve code comments

## Testing

Before submitting a PR, ensure:

- [ ] `./verify.sh` passes
- [ ] `./test.sh` passes
- [ ] Code compiles without warnings: `make all`
- [ ] Game runs correctly: `make run`
- [ ] No build artifacts are committed (check .gitignore)

## Questions?

Feel free to:
- Open an Issue for questions
- Start a Discussion on GitHub
- Comment on existing Issues/PRs

## License

By contributing, you agree that your contributions will be licensed under the same license as the project.
