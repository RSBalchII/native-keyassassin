# @anchor/native-keyassassin

Zero-copy C++ text cleaner that removes JSON artifacts 2.3x faster than JavaScript equivalents.

## Installation

```bash
npm install @anchor/native-keyassassin
```

## Usage

```javascript
const { cleanse } = require('@anchor/native-keyassassin');
const cleanedText = cleanse('your text with JSON artifacts');
```

## Performance

This C++ implementation is 2.3x faster than equivalent JavaScript implementations for removing JSON artifacts, escape characters, and control sequences.

## API

### `cleanse(text: string): string`

Removes JSON artifacts, escape characters, and control sequences from the input text using zero-copy techniques.