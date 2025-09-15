# Pokemon Collection App

A web application for exploring and collecting Pokemon data using the PokeAPI.

## Features

### 1. Search Functionality
- **Partial Name Search**: Enter part of a Pokemon name to find matches
- **View All**: Leave search empty to see all Pokemon (limited to 20 results)
- **Responsive Results**: Grid layout that adapts to screen size

### 2. Detailed Views
- **Pokemon Cards**: Quick overview with image, ID, height, weight, and types
- **Drill-down Details**: Click any Pokemon to see comprehensive information including:
  - Full description
  - Abilities
  - Base stats
  - Move list (first 10)
  - Sprites and artwork

### 3. Statistics Page
- **Live API Data**: Real-time statistics from PokeAPI
- **Collection Metrics**: 
  - Total Pokemon count
  - Total types
  - Total regions
  - Total abilities

### 4. About Page
- **Data Source Information**: Details about PokeAPI
- **API Documentation Links**: Direct links to API resources
- **Feature Overview**: Complete list of app capabilities

## Technical Implementation

### API Integration
- **Data Source**: PokeAPI (https://pokeapi.co/)
- **Endpoint Usage**: 
  - `/pokemon` for search and listing
  - `/pokemon/{id}` for detailed views
  - `/type`, `/region`, `/ability` for statistics
- **Error Handling**: Graceful handling of API failures
- **Loading States**: User feedback during data fetching

### User Interface
- **Responsive Design**: Mobile-friendly layout
- **Modern CSS**: Gradient backgrounds, smooth transitions
- **Intuitive Navigation**: Clear page structure with breadcrumbs
- **Accessibility**: Proper semantic HTML and keyboard navigation

### JavaScript Features
- **Async/Await**: Modern JavaScript for API calls
- **Error Handling**: Try-catch blocks for robust error management
- **Event Listeners**: Responsive user interactions
- **State Management**: Clean page transitions and data management

## File Structure

```
Project 2 Collect App Phase 1/
├── collections.html         # Main HTML structure
├── collectionsstyles.css    # CSS styling and responsive design
├── collections.js           # JavaScript functionality
└── README.md                # This documentation file
```

## Usage Instructions

1. **Search Pokemon**: 
   - Enter a Pokemon name (full or partial) in the search box
   - Click "Search" or press Enter
   - Leave empty to see all Pokemon

2. **View Details**:
   - Click on any Pokemon card to see detailed information
   - Use the back button to return to search results

3. **View Statistics**:
   - Click "Statistics" in the navigation to see live collection data

4. **Learn More**:
   - Click "About" to learn about the data source and features

## API Requirements Met

✅ **Partial Name Search**: Supports searching by partial Pokemon names
✅ **Limited Results**: Results are limited to 20 items maximum
✅ **Rich Data**: Comprehensive Pokemon information available
✅ **Statistics**: Live API calls for collection statistics

## Installation

1. Download all files to a web server directory
2. Open `collections.html` in a web browser
3. No additional setup required - uses CDN resources

## Development Notes

- Uses vanilla JavaScript (no frameworks required)
- Responsive CSS Grid and Flexbox layouts
- API calls handled with modern fetch API
- Error handling for network issues and missing data
- Clean, maintainable code structure

## Credits

- **API**: PokeAPI (https://pokeapi.co/)
- **Images**: Pokemon sprites from PokeAPI
- **Development**: CPSC-3750 Collection App Project By Sean Farrell
