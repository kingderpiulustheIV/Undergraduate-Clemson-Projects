# CPSC 4910 - Senior Computing Practicum

## Course Description
Capstone course where students work in teams to design, develop, and deploy a complete software system for a real-world client or sponsor. The course integrates knowledge from previous coursework and emphasizes software engineering practices, project management, teamwork, documentation, and professional presentation. Students follow the full software development lifecycle from requirements gathering through deployment and maintenance.

## Learning Objectives
- Apply software engineering principles to a real-world project
- Work effectively in a team-based development environment
- Practice agile development methodologies and project management
- Integrate multiple technologies into a cohesive system
- Develop professional documentation and presentations
- Implement security best practices in web applications
- Design and implement database-driven applications
- Deploy and maintain production-grade software
- Communicate technical concepts to non-technical stakeholders
- Practice code review and version control workflows

## Project: Safe Driver Incentive Program

### Project Overview
A comprehensive web application designed to incentivize safe driving behavior through a point-based rewards system. The platform connects drivers, sponsors, and administrators in a system where drivers earn points for safe driving, which can be redeemed for rewards from participating sponsors.

### Key Features
- **Driver Management**: User registration, profile management, and driver dashboard
- **Sponsor Portal**: Business account management and product catalog
- **Point System**: Tracking driver points and safe driving achievements
- **Wallet System**: Virtual wallet for point storage and transactions 
- **Product Catalog**: Sponsor-provided rewards and redemption system
- **Security Features**: Failed login tracking and account security 
- **Admin Dashboard**: System administration and oversight tools
- **Reporting**: Analytics and reporting for all user types

### Project Documentation
- **Good Driver Incentive Program-F25.pdf**: Project requirements and specifications
- **WALLET_HISTORY_IMPLEMENTATION.md**: Technical documentation for wallet feature
- **FAILED_LOGIN_SECURITY.md**: Security implementation details
- **docs-data.json**: Application documentation data

## Technology Stack

### Backend Techonologies
- **Django**: Python web framework for rapid development
- **Python 3.13**: Primary programming language
- **AWS EC2 Ubuntu x86-64 Instance** cloud computing resources used to host this project. 

### Database
- **MySQL/AWS**: Production database system hosted on AWS
- **SQLite3**: Development and testing database
- Django ORM for database abstraction

### Frontend Technologies
- HTML5/CSS3: User interface markup and styling
- JavaScript: Client-side interactivity
- Django Templates: Server-side rendering

### Python Dependencies
- **Django**: Web framework
- **mysqlclient**: MySQL database adapter for Python
- **Pipenv**: Dependency management and virtual environments

### Development Tools
- **Git**: Version control system
- **Pipenv**: Virtual environment and dependency management
- **VS Code/PyCharm**: Integrated development environment
- **Django Admin**: Built-in administration interface

### Django Architecture Components
- **Models** (models.py): Database schema and ORM definitions
- **Views** (views.py): Request handling and business logic
- **URLs** (urls.py): URL routing and endpoint definitions
- **Forms** (forms.py): Form handling and validation
- **Templates**: HTML templates for rendering
- **Admin** (admin.py): Admin interface configuration
- **Migrations**: Database schema version control

### Features Implemented
- User authentication and authorization
- Role-based access control (Driver, Sponsor, Admin)
- Profile management with avatar support
- Product caching system (product_cache.py)
- Custom decorators for view protection
- Address management system
- Wallet and transaction history
- Failed login attempt tracking

### Security Features
- User authentication with Django's built-in system
- Password security and hashing
- Failed login attempt monitoring
- Role-based access control
- CSRF protection
- Session management

## Project Structure
```
F25-Team05 Senior Project/
├── safedriverprogram/          # Main Django project
│   ├── manage.py               # Django management script
│   ├── safedriverprogram/      # Project configuration
│   │   ├── settings.py         # Django settings
│   │   ├── urls.py            # Root URL configuration
│   │   ├── wsgi.py            # WSGI configuration
│   │   └── asgi.py            # ASGI configuration
│   ├── driver_program/         # Main application
│   │   ├── models.py          # Database models
│   │   ├── views.py           # View functions
│   │   ├── urls.py            # URL routing
│   │   ├── forms.py           # Form definitions
│   │   ├── admin.py           # Admin configuration
│   │   ├── decorators.py      # Custom decorators
│   │   ├── product_cache.py   # Product caching
│   │   └── migrations/        # Database migrations
│   ├── Database/               # Database utilities
│   └── db.sqlite3             # Development database
├── Pipfile                     # Dependency specifications
├── Pipfile.lock               # Locked dependencies
└── README.md                  # Project documentation
```

## Setup and Requirements

### Software Requirements
- Python 3.13
- Pipenv for virtual environment management
- MySQL Server (production) or SQLite (development)
- Web browser (Chrome, Firefox, Edge)
- Git for version control

### Installation Steps
1. Clone the repository
2. Install Python 3.13
3. Install Pipenv: `pip install pipenv`
4. Install dependencies: `pipenv install`
5. Activate virtual environment: `pipenv shell`
6. Run migrations: `python manage.py migrate`
7. Create superuser: `python manage.py createsuperuser`
8. Run development server: `python manage.py runserver`

### Database Setup
- Development: SQLite (included)
- Production: MySQL/MariaDB with mysqlclient driver
- Migrations managed through Django's migration system

### Environment Configuration
- Configure database settings in settings.py
- Set SECRET_KEY for production
- Configure static files and media handling
- Set up email backend for notifications

## Work Type
This is a **team-based capstone project** (Fall 2025 - Team 05).
- Collaborators include:
- Aaron Corbin
- Sean Farrell
- Mills Grimsley
- Will Lovin
- Diarra Ndiaye


### Team Collaboration
- Agile development methodology
- Sprint-based development cycles
- Code reviews and pair programming
- Version control with Git
- Regular team meetings and stand-ups
- Client/sponsor communication

## Development Practices
- Version control with Git
- Feature branch workflow
- Code reviews before merging
- Database migrations for schema changes
- Documentation of major features
- Test-driven development (tests.py)
- Continuous integration and deployment

## Key Learning Outcomes
- Full-stack web development
- Database design and implementation
- User authentication and security
- REST API design principles
- Deployment and DevOps basics
- Team collaboration and communication
- Project management and documentation
- Client interaction and requirements gathering

## Project Management
- Requirements analysis and specification
- System design and architecture
- Implementation and coding
- Testing and quality assurance
- Documentation and user guides
- Deployment and maintenance planning
- Client presentations and demonstrations
